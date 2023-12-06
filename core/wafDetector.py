import json
import re
import sys

from core.requester import requester
from core.log import setup_logger

logger = setup_logger(__name__)

def wafDetector(url, params, headers, GET, delay, timeout):
    # JSON 파일에서 WAF 시그니처를 로드합니다.
    with open(sys.path[0] + '/db/wafSignatures.json', 'r') as file:
        wafSignatures = json.load(file)

    # WAF를 유도하기 충분한 소음이 있는 페이로드
    noise = '<script>alert("XSS")</script>'
    params['xss'] = noise

    # 소음이 주입된 페이로드로 요청을 보냅니다.
    response = requester(url, params, headers, GET, delay, timeout)
    page = response.text
    code = str(response.status_code)
    headers = str(response.headers)
    
    logger.debug('Waf Detector code: {}'.format(code))
    logger.debug_json('Waf Detector headers:', response.headers)

    if int(code) >= 400:
        bestMatch = [0, None]
        for wafName, wafSignature in wafSignatures.items():
            score = 0
            pageSign = wafSignature['page']
            codeSign = wafSignature['code']
            headersSign = wafSignature['headers']

            if pageSign:
                if re.search(pageSign, page, re.I):
                    score += 1

            if codeSign:
                if re.search(codeSign, code, re.I):
                    score += 0.5  # HTTP 코드는 강력한 지표가 아니므로 전체 점수를 작은 양으로 증가시킵니다.

            if headersSign:
                if re.search(headersSign, headers, re.I):
                    score += 1

            # 이전 것보다 WAF의 전체 점수가 더 높으면 갱신합니다.
            if score > bestMatch[0]:
                del bestMatch[:]  # 이전 것을 삭제합니다.
                bestMatch.extend([score, wafName])  # 이 것을 추가합니다.

        # 가장 높은 점수를 가진 WAF가 있는 경우 해당 WAF 이름을 반환합니다.
        if bestMatch[0] != 0:
            return bestMatch[1]
        else:
            return None
    else:
        return None
