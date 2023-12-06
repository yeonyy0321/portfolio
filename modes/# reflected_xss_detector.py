# reflected_xss_detector.py
import copy
from urllib.parse import urlparse

import sys
import os
project_root = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
sys.path.insert(0, project_root)
from core.colors import green, end
from core.config import xsschecker
from core.fuzzer import fuzzer
from core.requester import requester
from core.utils import getUrl, getParams
from core.wafDetector import wafDetector
from core.log import setup_logger



# 위의 코드 추가
target_url = "http://testphp.vulnweb.com"  # 대상 URL
param_data = {"param1": "value1", "param2": "value2"}  # URL 또는 POST 데이터에 사용될 매개변수
encoding = "utf-8"  # 인코딩 설정
headers = {"User-Agent": "Mozilla/5.0"}  # HTTP 헤더
delay = 0  # 요청 딜레이 (초)
timeout = 10  # 요청 타임아웃 (초)

logger = setup_logger(__name__)

def detect_reflected_xss(target, paramData, encoding, headers, delay, timeout):
    GET, POST = (False, True) if paramData else (True, False)
    
    if not target.startswith('http'):
        try:
            response = requester('https://' + target, {},
                                 headers, GET, delay, timeout)
            target = 'https://' + target
        except:
            target = 'http://' + target
    logger.debug('Reflected XSS target: {}'.format(target))
    
    host = urlparse(target).netloc
    logger.debug('Reflected XSS host: {}'.format(host))
    url = getUrl(target, GET)
    logger.debug('Reflected XSS url: {}'.format(url))
    params = getParams(target, paramData, GET)
    logger.debug_json('Reflected XSS params:', params)
    
    if not params:
        logger.error('No parameters to test.')
        quit()
    
    if WAF:
        logger.error('WAF detected: %s%s%s' % (green, WAF, end))
        # 여기에서 WAF가 탐지된 경우, 분석 중단 및 메시지 출력
        logger.error('Analysis failed: WAF detected, cannot proceed with the test.')
        return

    logger.good('WAF Status: %sOffline%s' % (green, end))

    for paramName in params.keys():
        logger.info('Testing parameter: %s' % paramName)
        paramsCopy = copy.deepcopy(params)
        paramsCopy[paramName] = xsschecker
        # 취약점이 발견되면 로그에 기록
        if fuzzer(url, paramsCopy, headers, GET, delay, timeout, WAF, encoding):
            logger.error('Vulnerability Detected: Reflected XSS in parameter "{}"'.format(paramName))
        else:
            # 취약점이 발견되지 않은 경우
            logger.good('Analysis successful: No reflected XSS vulnerability detected in parameter "{}"'.format(paramName))