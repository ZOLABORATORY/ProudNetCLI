3개의 프로젝트가 존재합니다.

1) PNWrap2 (C++ / CLI)
	프라우드넷 DB Cache2 system 을 CLI로 wrapping 한 dll 파일을 생성해줍니다.
	(당연하지만) 이 DLL은 C# 에서도 사용가능합니다.

2) DBCacheServer (C++)
	프라우드넷 DBCache2 Server 예제를 갖고 약간만 변형해서 만들은 예제입니다.
	크게 다르지 않으니 어렵지 않을 겁니다.

	*전 mariadb 를 이용해 만든 제 커스텀 ODBC드라이버로 DB서버에 접속시켰습니다.
	모든 분들의 서버 셋팅마다 이 ODBC들은 따로 입력해서 만드실테니 제가 임의로 만들어드릴수는 없을것입니다;;
	다만 SimpleDB2ServerDlg.cpp 의 16줄 dbmsStringForFormat 변수를 자신에게 맞게 잘 편집해서 쓰시면 될듯 합니다.

	*DB 서버의 URL, PORT, USERID, PASSWORD, DB이름은 SimpleDB2ServerDlg::TrialStartDbServer 함수안에 하드코드되어 있습니다.
	이부분을 자신의 서버에 맞게 변경해서 쓰시면 될 것입니다.

	*SimpleDB2ServerDlg::TrialStartDbServer 아래 root테이블과 child 테이블 추가하는부분은 프라우드넷 샘플과 동일하게 해놨습니다!
	제가 임의로 제것을 넣어놓았지만 커스텀 해서 쓰십시오.

	실행하자마자 접속을 시도합니다 디버거 켜놓고 해보시길...

3) CSharpServer (C#)
	이쪽이 DBCacheServer 에 접속해서 기능들을 사용하는 실제 C# 서버부분입니다.
	실행하자마자 DBCacheSystem.cs 의 Example_Coroutine을 사용 합니다.

	*제가 이벤트핸들링 방식을 너무 싫어해서(...) 코루틴방식으로 변경해서 만들었는데 이부분이 성능저하의 주원인이지 싶습니다.
	변경해서 쓰시면 아마 빠를수도 있습니다. 다만 저도 테스트를 안해봐서 확신은 무리...

	*샘플 코드는 저의 DB를 상정해서 제작되어 있지만 유추가능하실거라 생각합니다.
	DBCache.cs 의 함수 리스트를 보시고 프라우드넷 DBCache2 공식설명서의 레퍼런스를 보시면 각각 기능이 어떻게 1:1 대응되어있는지 아실 수 있을겁니다.



거듭 당부하지만 제가 쓰기편한대로 만들다보니 성능이 너무 떨어져 사용과 개발을 포기한 상태입니다.
이걸 사용하시려면 고민해보세요!