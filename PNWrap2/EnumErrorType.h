#pragma once

//�׳� �ܺ� ���ÿ����� ��-�� �� �ڵ��� ������� ���� �ڵ� �̸��տ� Wrap �� ����
namespace PNWrap2
{
	//tagVARENUM
	enum VARENUM
	{
		VT_EMPTY = 0x0000,
		VT_NULL = 0x0001,
		VT_I2 = 0x0002,
		VT_I4 = 0x0003,
		VT_R4 = 0x0004,
		VT_R8 = 0x0005,
		VT_CY = 0x0006,
		VT_DATE = 0x0007,
		VT_BSTR = 0x0008,
		VT_DISPATCH = 0x0009,
		VT_ERROR = 0x000A,
		VT_BOOL = 0x000B,
		VT_VARIANT = 0x000C,
		VT_UNKNOWN = 0x000D,
		VT_DECIMAL = 0x000E,
		VT_I1 = 0x0010,
		VT_UI1 = 0x0011,
		VT_UI2 = 0x0012,
		VT_UI4 = 0x0013,
		VT_I8 = 0x0014,
		VT_UI8 = 0x0015,
		VT_INT = 0x0016,
		VT_UINT = 0x0017,
		VT_VOID = 0x0018,
		VT_HRESULT = 0x0019,
		VT_PTR = 0x001A,
		VT_SAFEARRAY = 0x001B,
		VT_CARRAY = 0x001C,
		VT_USERDEFINED = 0x001D,
		VT_LPSTR = 0x001E,
		VT_LPWSTR = 0x001F,
		VT_RECORD = 0x0024,
		VT_INT_PTR = 0x0025,
		VT_UINT_PTR = 0x0026,
		VT_ARRAY = 0x2000,
		VT_BYREF = 0x4000
	};

	enum WrapMessagePriority
	{
		/**
		\~korean
		�ſ� ���� �켱����. connectivity test�� ���� ping � ����. PN ����

		\~english TODO:translate needed.

		\~chinese
		ު������?�?�������?��connectivity test��ping����PN ?�ġ�

		\~japanese
		\~
		*/
		MessagePriority_Ring0 = 0,

		/**
		\~korean
		PN ����

		\~english TODO:translate needed.

		\~chinese
		PN ?�ġ�

		\~japanese
		\~
		*/
		MessagePriority_Ring1,

		/**
		\~korean
		���� �켱����

		\~english TODO:translate needed.

		\~chinese
		����?�?��

		\~japanese
		\~
		*/
		MessagePriority_High,

		/**
		\~korean
		���� �켱����. ���� ���� ����.

		\~english TODO:translate needed.

		\~chinese
		����?�?������������

		\~japanese
		\~
		*/
		MessagePriority_Medium,

		/**
		\~korean
		���� �켱����

		\~english TODO:translate needed.

		\~chinese
		���?�?��

		\~japanese
		\~
		*/
		MessagePriority_Low,

		/**
		\~korean
		�ſ� ���� �켱����
		PN ����

		\~english TODO:translate needed.

		\~chinese
		ު�����?�?��
		PN ?�ġ�

		\~japanese
		\~
		*/
		MessagePriority_Ring99,

		/**
		\~korean
		����ڴ� ����� �� ���� ��

		\~english TODO:translate needed.

		\~chinese
		��?����������?��

		\~japanese
		\~
		*/
		MessagePriority_LAST,
	};

	// Ȧ��Ī ��Ŷ�� ���� �� �ִ�. �̰��� Ʈ������ �����ϸ� �ȵǹǷ� �켱������ �������� �д�.
	static const WrapMessagePriority MessagePriority_Holepunch = MessagePriority_Ring99;

	// ����: �̰͵� �ٲٸ� ProudClr namespace�� ���� �ɺ��� �����ؾ� �Ѵ�.

	public enum WrapMessageReliability
	{
		MessageReliability_Unreliable = 0,
		MessageReliability_Reliable,
		MessageReliability_LAST,
	};

	// ����: �̰͵� �ٲٸ� ProudClr namespace�� ���� �ɺ��� �����ؾ� �Ѵ�.

	/**
	\~korean
	���� Ÿ�� �ڵ�

	\~english TODO:translate needed.

	\~chinese
	???����?��

	\~japanese
	\~
	*/
	public enum WrapErrorType
	{
		/**
		\~korean
		����. ���� ����.

		\~english TODO:translate needed.

		\~chinese
		����?��??��

		\~japanese
		\~
		*/
		ErrorType_Ok = 0,

		/**
		\~korean
		���� ��Ȳ �߻�

		\~english TODO:translate needed.

		\~chinese
		?��������?��

		\~japanese
		\~
		*/
		ErrorType_Unexpected,

		/**
		\~korean
		�̹� ����Ǿ� ����

		\~english TODO:translate needed.

		\~chinese
		�?��?��??
		\~japanese
		\~
		*/
		ErrorType_AlreadyConnected,

		/**
		\~korean
		TCP ���� ����

		\~english TODO:translate needed.

		\~chinese
		TCP ?����?��

		\~japanese
		\~
		*/
		ErrorType_TCPConnectFailure,

		/**
		\~korean
		�߸��� ��ĪŰ

		\~english TODO:translate needed.

		\~chinese
		??��??key��

		\~japanese
		\~
		*/
		ErrorType_InvalidSessionKey,

		/**
		\~korean
		��ȣȭ�� ��������

		\~english TODO:translate needed.

		\~chinese
		ʥ����?��

		\~japanese
		\~
		*/
		ErrorType_EncryptFail,

		/**
		\~korean
		��Ŀ�� ���� �����͸� �����߰ų� ��ȣȭ�� ��������

		\~english TODO:translate needed.

		\~chinese
		����ʦ��?����???�ߣ��������?��?��

		\~japanese
		\~
		*/
		ErrorType_DecryptFail,

		/**
		\~korean
		���� ���� ������ �ʹ� ���� �ɷ��� ���� ó����

		\~english TODO:translate needed.

		\~chinese
		����?��?��????���?��

		\~japanese
		\~
		*/
		ErrorType_ConnectServerTimeout,

		/**
		\~korean
		���� ������ ���� �������� ������ �ٸ�

		\~english TODO:translate needed.

		\~chinese
		��?��?����????�������ҡ�

		\~japanese
		\~
		*/
		ErrorType_ProtocolVersionMismatch,

		/**
		\~korean
		������ ������ �ǵ������� �ź�����

		\~english TODO:translate needed.

		\~chinese
		��?��ͺ����??�ȡ�

		\~japanese
		\~
		*/
		ErrorType_NotifyServerDeniedConnection,

		/**
		\~korean
		���� ���� ����!

		\~english TODO:translate needed.

		\~chinese
		��?��?������

		\~japanese
		\~
		*/
		ErrorType_ConnectServerSuccessful,

		/**
		\~korean
		����� ȣ��Ʈ���� ������ ��������

		\~english TODO:translate needed.

		\~chinese
		?۰��������?�ȡ�

		\~japanese
		\~
		*/
		ErrorType_DisconnectFromRemote,

		/**
		\~korean
		���� ȣ��Ʈ���� ������ ��������

		\~english TODO:translate needed.

		\~chinese
		??��������?�ȡ�

		\~japanese
		\~
		*/
		ErrorType_DisconnectFromLocal,

		/**
		\~korean
		������ ��Ȳ�� �ҷ��� �� �ִ� ���ڰ� ����

		\~english TODO:translate needed.

		\~chinese
		���ʦ��������???�����ȡ�

		\~japanese
		\~
		*/
		ErrorType_DangerousArgumentWarning,

		/**
		\~korean
		�� �� ���� ���ͳ� �ּ�

		\~english TODO:translate needed.

		\~chinese
		ڱ�����??�򣡣

		\~japanese
		\~
		*/
		ErrorType_UnknownAddrPort,

		/**
		\~korean
		���� �غ� ����

		\~english TODO:translate needed.

		\~chinese
		��?����?���롣

		\~japanese
		\~
		*/
		ErrorType_ServerNotReady,

		/**
		\~korean
		���� ������ listen�� ������ �� �����ϴ�. TCP �Ǵ� UDP ������ �̹� ������� ��Ʈ���� Ȯ���Ͻʽÿ�.

		\~english TODO:translate needed.

		\~chinese
		����?���?��socket��listen��???TCP���UDPsocket���������������ӮϢ��

		\~japanese
		\~
		*/
		ErrorType_ServerPortListenFailure,

		/**
		\~korean
		�̹� ��ü�� �����մϴ�.

		\~english TODO:translate needed.

		\~chinese
		?������

		\~japanese
		\~
		*/
		ErrorType_AlreadyExists,

		/**
		\~korean
		������ �źεǾ����ϴ�.
		- \ref dbc2_nonexclusive_overview ��ɿ���, DB cache server�� ������ ���� ����� ���� �ʰڴٴ� ������ �Ǿ� ������ �߻��� �� �ֽ��ϴ�.
		- ������ ��Ÿ�̻��� OS���� �����ڱ����� ���� CNetUtil::EnableTcpOffload( bool enable ) �Լ��� ȣ��Ǹ� �߻��� �� �ֽ��ϴ�.

		\~english
		Access denied.
		- At \ref dbc2_nonexclusive_overview function, it could occur if a function that DB cache server does not use exclusive access function has been set.
		- At OS over window vista, It could occur when CNetUtil::EnableTcpOffload( bool enable ) function is called without administration authority.

		\~chinese
		��������?��
		- �\ref dbc2_nonexclusive_overview%����߾������DB cache server��?������������������������?��??���??��
		- �window��vista �߾��OS�飬?��η��??������ CNetUtil::EnableTcpOffload ( bool enable )��?��?��ʦ��??���??��

		\~japanese
		���Ϊ���������ު�����
		- \ref dbc2_nonexclusive_overview Ѧ����, DB cache server��ު?�������Ѧ�������Ī��ʪ������Ҫ���ƪ����?�檹��ʦ����������ު���
		- Window Vista�߾��OS��η���?�ڪʪ��� CNetUtil::EnableTcpOffload( bool enable ) ??�������󪵪���?�檹��ʦ����������ު���

		\~
		*/
		ErrorType_PermissionDenied,

		/**
		\~korean
		�߸��� session Guid�Դϴ�.

		\~english TODO:translate needed.

		\~chinese
		??��session Guid��

		\~japanese
		\~
		*/
		ErrorType_BadSessionGuid,

		/**
		\~korean
		�߸��� credential�Դϴ�.

		\~english TODO:translate needed.

		\~chinese
		??��credential��

		\~japanese
		\~
		*/
		ErrorType_InvalidCredential,

		/**
		\~korean
		�߸��� hero name�Դϴ�.

		\~english TODO:translate needed.

		\~chinese
		??��hero name��

		\~japanese
		\~
		*/
		ErrorType_InvalidHeroName,

		/**
		\~korean
		�ε� ������ unlock �� lock �� �� ������ �߻��ߴ�

		\~english TODO:translate needed.

		\~chinese
		ʥ??��unlock�����lock ��?����󢡣

		\~japanese
		\~
		*/
		ErrorType_LoadDataPreceded,

		/**
		\~korean
		��� �Ķ���� AdjustedGamerIDNotFilled�� ä������ �ʾҽ��ϴ�.

		\~english TODO:translate needed.

		\~chinese
		?��??AdjustedGamerIDNotFilled?����?����

		\~japanese
		\~
		*/
		ErrorType_AdjustedGamerIDNotFilled,

		/**
		\~korean
		�÷��̾� ĳ���Ͱ� �������� �ʽ��ϴ�.

		\~english TODO:translate needed.

		\~chinese
		��ʫ���������

		\~japanese
		\~
		*/
		ErrorType_NoHero,

		/**
		\~korean
		���� �׽�Ʈ ����

		\~english
		Unit test failed

		\~chinese
		?�??��?��

		\~japanese
		\~
		*/
		ErrorType_UnitTestFailed,

		/**
		\~korean
		peer-to-peer UDP ����� �������ϴ�.

		\~english TODO:translate needed.

		\~chinese
		peer-to-peer UDP �������ݡ�

		\~japanese
		\~
		*/
		ErrorType_P2PUdpFailed,

		/**
		\~korean
		P2P reliable UDP�� �����߽��ϴ�.

		\~english TODO:translate needed.

		\~chinese
		P2P reliable UDP��?��

		\~japanese
		\~
		*/
		ErrorType_ReliableUdpFailed,

		/**
		\~korean
		Ŭ���̾�Ʈ-���� UDP ����� �������ϴ�.

		\~english TODO:translate needed.

		\~chinese
		��ʫ-��?����UDP�������ݡ�

		\~japanese
		\~
		*/
		ErrorType_ServerUdpFailed,

		/**
		\~korean
		�� �̻� ���� �Ҽӵ� P2P �׷��� �����ϴ�.

		\~english TODO:translate needed.

		\~chinese
		�?�������?��P2P?��

		\~japanese
		\~
		*/
		ErrorType_NoP2PGroupRelation,

		/**
		\~korean
		����� ���� �Լ�(RMI ���� ��ƾ Ȥ�� �̺�Ʈ �ڵ鷯)���� exception�� throw�Ǿ����ϴ�.

		\~english TODO:translate needed.

		\~chinese
		?��?��?��?��RMI ��������������handler��exception ��throw��

		\~japanese
		\~
		*/
		ErrorType_ExceptionFromUserFunction,

		/**
		\~korean
		������� ��û�� ���� �����Դϴ�.

		\~english TODO:translate needed.

		\~chinese
		��?�?��������?��

		\~japanese
		\~
		*/
		ErrorType_UserRequested,

		/**
		\~korean
		�߸��� ��Ŷ �����Դϴ�. ����� ȣ��Ʈ�� ��ŷ�Ǿ��ų� ������ �� �ֽ��ϴ�.

		\~english TODO:translate needed.

		\~chinese
		??��?�������ҡ�ʦ����?۰���������������ש�ס�

		\~japanese
		\~
		*/
		ErrorType_InvalidPacketFormat,

		/**
		\~korean
		�ʹ� ū ũ���� �޽�¡�� �õ��Ǿ����ϴ�. ��������ο� �����Ͻʽÿ�. �ʿ�� \ref message_length  �� �����Ͻʽÿ�.

		\~english TODO:translate needed.

		\~chinese
		??������?����messaging��?�?��?��ݻ�����???��\ref message_length%��

		\~japanese
		\~
		*/
		ErrorType_TooLargeMessageDetected,

		/**
		\~korean
		Unreliable �޼����� encrypt �Ҽ� �����ϴ�.

		\~english TODO:translate needed.

		\~chinese
		Unreliable ��������encrypt��

		\~japanese
		\~
		*/
		ErrorType_CannotEncryptUnreliableMessage,

		/**
		\~korean
		�������� �ʴ� ���Դϴ�.

		\~english TODO:translate needed.

		\~chinese
		�������?��

		\~japanese
		\~
		*/
		ErrorType_ValueNotExist,

		/**
		\~korean
		Ÿ�Ӿƿ� �Դϴ�.

		\~english TODO:translate needed.

		\~chinese
		��?��

		\~japanese
		\~
		*/
		ErrorType_TimeOut,

		/**
		\~korean
		�ε�� �����͸� ã���� �����ϴ�.

		\~english TODO:translate needed.

		\~chinese
		����?��ʥ?��?�ߡ�

		\~japanese
		\~
		*/
		ErrorType_LoadedDataNotFound,

		/**
		\~korean
		\ref send_queue_heavy . �۽� queue�� ����ġ�� Ŀ�����ϴ�.

		\~english TODO:translate needed.

		\~chinese
		\ref send_queue_heavy��?��queue?�ޡ�

		\~japanese
		\~
		*/
		ErrorType_SendQueueIsHeavy,

		/**
		\~korean
		Heartbeat�� ��������� �ʹ� ����

		\~english TODO:translate needed.

		\~chinese
		Heartbeat ��г��ط��

		\~japanese
		\~
		*/
		ErrorType_TooSlowHeartbeatWarning,

		/**
		\~korean
		�޽��� ������ ���� �Ͽ����ϴ�.

		\~english TODO:translate needed.

		\~chinese
		����??��?��

		\~japanese
		\~
		*/
		ErrorType_CompressFail,

		/**
		\~korean
		Ŭ���̾�Ʈ ������ listen�� ������ �� �����ϴ�. TCP �Ǵ� UDP ������ �̹� ������� ��Ʈ���� Ȯ���Ͻʽÿ�.

		\~english
		Unable to start listening of client socket. Must check if either TCP or UDP socket is already in use.

		\~chinese
		����?���ʫsocket��listen��???TCP���UDP socketӮϢ�����������顣

		\~japanese
		\~
		*/
		ErrorType_LocalSocketCreationFailed,

		/**
		\~korean
		Socket�� ������ �� Port Pool �� port number���� bind�� �����߽��ϴ�. ��� ������ port number�� ���Ǿ����ϴ�. Port Pool�� ������ ������� Ȯ���Ͻʽÿ�.

		\~english
		Failed binding to local port that defined in Port Pool. Please check number of values in Port Pool are sufficient.

		\~chinese
		����socket��?����Port Pool?port number��bind��?������port number���������ġ�???Port Pool��??�������¡�

		\~japanese
		\~
		*/
		Error_NoneAvailableInPortPool,

		/**
		\~korean
		Port pool �� ���� �� �ϳ� �̻��� �߸��Ǿ����ϴ�. ��Ʈ�� 0(���� ��Ʈ ���ε�)���� �ϰų� �ߺ����� �ʾҴ��� Ȯ���Ͻʽÿ�.

		\~english
		Range of user defined port is wrong. Set port to 0(random port binding) or check if it is overlaped.

		\~chinese
		Port pool ����?�߾��??��?��??��ӮϢ??0������ӮϢbinding�����������?��

		\~japanese
		\~
		*/
		ErrorType_InvalidPortPool,

		/**
		\~korean
		��ȿ���� ���� HostID ���Դϴ�.

		\~english
		Invalid HostID.

		\~chinese
		������HostID��

		\~japanese
		\~
		*/
		ErrorType_InvalidHostID, // CODEREV-FORCERELAY: enum ErrorType�� ������ ���ϼ̱���. �̷��� ��� TypeToString_Kor, TypeToString_Eng,TypeToString_Chn���� ������ ���ؾ� �մϴ�. C#,AS,Java���������� ���������Դϴ�.

								 /**
								 \~korean
								 ����ڰ� ��ȭ�ϴ� �޽��� ó�� �ӵ����� ���������� ���̴� �޽����� �ӵ��� �� �����ϴ�.
								 ����ġ�� �ʹ� ���� �޽����� �۽��Ϸ��� �ߴ���, Ȥ�� ������� �޽��� ���� �Լ��� ����ġ�� ������ �۵��ϰ� �ִ��� Ȯ���Ͻʽÿ�.

								 \~english
								 The speed of stacking messages are higher than the speed of processing them.
								 Check that you are sending too many messages, or your message processing routines are running too slowly.

								 \~chinese
								 �������?��������?��??��������
								 ???�?����?�������������?������?��?ط��
								 \~
								 \~
								 */
		ErrorType_MessageOverload,


		/** Accessing database failed. For example, query statement execution failed. You may see the details from comment variable.
		*/
		ErrorType_DatabaseAccessFailed,

		/**
		\~korean �޸𸮰� �����մϴ�.

		\~english Out of memory.

		\~chinese ?������.

		\~japanese ����?�����ު���
		\~
		*/
		ErrorType_OutOfMemory,

		/** �������� ������ �������� ���� ���� ����� �����Ǿ�����, �̰� ������ �����߽��ϴ�. */
		ErrorType_AutoConnectionRecoveryFailed,
	};

	/**
	\~korean
	ProudNet ȣ��Ʈ �ĺ���

	\~english TODO:translate needed.

	\~chinese
	ProudNet ���??��

	\~japanese
	\~
	*/
	public enum WrapHostID
	{
		/**
		\~korean
		����

		\~english
		None

		\~chinese
		��

		\~japanese
		\~
		*/
		HostID_None = 0,

		/**
		\~korean
		����

		\~english
		Server

		\~chinese
		��?��

		\~japanese
		\~
		*/
		HostID_Server = 1,

		/**
		\~korean
		(������)

		\~english
		(Do not use it)

		\~chinese
		��������ģ�

		\~japanese
		\~
		*/
		HostID_Last = 2
	};

	public enum Wrap_RmiID
	{
		RmiID_None = 0,
		RmiID_Last = 65535, // marmalade���� RMI ID�� word�� ���� �����ϱ� ����.
	};

	/** \~korean ��� ������ �߻��ϴ� �α��� ���� Ÿ���Դϴ�.
	\~english It is a category type of the log occurred within the module.
	\~chinese �ټ???����Log��??
	\~japanese �⫸��?��?��?�檹����Ϋ��ƫ���?�����תǪ���
	\~ */
	public enum WrapLogCategory
	{
		/** \~korean �⺻ �ý���
		\~english Basic System
		\~chinese ��?ͧ?
		\~japanese ���⫷���ƫ�
		\~ */
		LogCategory_System,
		/** \~korean TCP ��� ����
		\~english Relevant to TCP communication
		\~chinese ��? TCP ����
		\~japanese TCP����?֧
		\~ */
		LogCategory_Tcp,
		/** \~korean UDP ��� ����
		\~english Relevant to UDP communication
		\~chinese ��? UDP ����
		\~japanese UDP����?֧
		\~ */
		LogCategory_Udp,
		/** \~korean P2P ��� ����
		\~english Relevant to P2P communication
		\~chinese ��? P2P ����
		\~japanese P2P����?֧
		\~ */
		LogCategory_P2P
	};

	/**
	\~korean
	��ŷ�� ����

	\~english
	Type of hacking

	\~chinese
	������??��

	\~japanese
	\~
	*/
	public enum WrapHackType
	{
		/**
		\~korean
		��ŷ �ƴ�

		\~english
		No hacking

		\~chinese
		�������ԡ�

		\~japanese
		\~
		*/
		HackType_None,

		/**
		\~korean
		���ǵ���

		\~english
		Speek hack

		\~chinese
		����hack��

		\~japanese
		\~
		*/
		HackType_SpeedHack,

		/**
		\~korean
		��Ŷ ����

		\~english
		Handle packet

		\~chinese
		?�������¡�

		\~japanese
		\~
		*/
		HackType_PacketRig,
	};

	/**
	\~korean
	Ÿ ȣ��Ʈ���� ���� ����

	\~english
	Connection status with other hosts

	\~chinese
	?���������?��??��

	\~japanese
	\~
	*/
	public enum WrapConnectionState
	{
		/**
		\~korean
		������ ������ ����

		\~english
		Disconnected condition

		\~chinese
		?����?��??��

		\~japanese
		\~
		*/
		ConnectionState_Disconnected,

		/**
		\~korean
		���� �õ��� ������ ���� ����� �� �� ���� ����

		\~english
		Tried connecting but result is unknown

		\~chinese
		?�???�ȣ�ӣ�����Գ?����??��

		\~japanese
		\~
		*/
		ConnectionState_Connecting,

		/**
		\~korean
		���� ������ ������ ����

		\~english
		Succeed to connect

		\~chinese
		?��?��������??��

		\~japanese
		\~
		*/
		ConnectionState_Connected,

		/**
		\~korean
		���� ���� ������ �������� ����

		\~english
		Disconnecting is in progress

		\~chinese
		�?��?�����?����??��

		\~japanese
		\~
		*/
		ConnectionState_Disconnecting,
	};

	/**
	\~korean
	TCP fallback�� �ǵ������� ������ ���� ���

	\~english
	How to intentially use TCP fallback

	\~chinese
	ͺ��?��TCP fallback?��۰����

	\~japanese
	\~
	*/
	public enum WrapFallbackMethod // ������ ���� ������ enum ���� ������ ��
	{
		/**
		\~korean
		Fallback�� ����. �� ���� �� peer���� UDP ����� ��� �����.

		\~english
		No Fallback. In other words, UDP communication to both server and peer are in use.

		\~chinese
		���Fallback��?������ݻ����?����?peer��UDP���ᡣ

		\~japanese
		\~
		*/
		FallbackMethod_None,
		/**
		\~korean
		�������� UDP ����� �����ϵ� Ÿ Peer����� UDP ��Ÿ��� ���ܵ� ������ ó���Ѵ�. �Ͻ��� ��Ʈ���� ���п� ������ ��Ȳ�� �����Ѵ�. ���� ������ ����.

		\~english
		Regards that UDP with server is sustained but UDP with other peers to be disconnected. Reproduce a circumstance similar to a temporary port mapping failure. This is the lowest option with weakest impact.

		\~chinese
		?�?��?����UDP���ᣬ?��?��?����peer��UDP������?���?��?��ӮϢ�����?��?������?��˭�����

		\~japanese
		\~
		*/
		FallbackMethod_PeersUdpToTcp,
		/**
		\~korean
		�������� UDP ����� ���ܵ� ������ ó���Ѵ�. �Ͻ��� ��Ʈ���� ���п� ������ ��Ȳ�� �����Ѵ�. �ƿ﷯ Peer����� UDP ��ŵ� ���ܵȴ�. �߰� ������.

		\~english
		Regards that UDP with server is disconnected. Reproduce a circumstance similar to a temporary port mapping failure. On top of that, it also disconnects UDP with peers. Intermediate impact.


		\~chinese
		?��?��?����peer��UDP������?���?��?��ӮϢ�����?��?������?��?peer��UDP���������?��˭��������

		\~japanese
		\~
		*/
		FallbackMethod_ServerUdpToTcp,
		/**
		\~korean
		Ŭ���̾�Ʈ�� UDP ������ �ƿ� �ݾƹ�����. �������� UDP ������ ���ϰ� �Ѵ�. ���� ������ ����.
		- Proud.CNetServer.SetDefaultFallbackMethod ������ ����� �� ����.

		\~english
		All UDP sockets of client will be shut down. UDP restoration will never be possible. Strongest impact.
		- Unable to use in Proud.CNetServer.SetDefaultFallbackMethod

		\~chinese
		����??��ʫ��UDPsocket����?��������UDP��?��˭�����ԡ�

		\~japanese
		\~
		*/
		FallbackMethod_CloseUdpSocket,
	};

	/**
	\~korean
	Ŭ���̾�Ʈ�� ���� P2P ����� ���� Ȧ��Ī�� �����ϴ� ����

	\~english
	Conditions to start hole-punching for direct P2P communication among clients

	\~chinese
	?����ʫ��??�����P2P����������?�졣

	\~japanese
	\~
	*/
	public enum WrapDirectP2PStartCondition
	{
		/**
		\~korean
		�� �ʿ��� ��Ȳ�� �ƴ� �̻� Ȧ��Ī�� ���� �ʴ´�. �����ϸ� �̰��� ���� ���� ����.

		\~english
		Unless really needed, it is recommended not to do hole-punching. Using this is strongly recommended.

		\~chinese
		�����������?��?��?�����ס�������??��

		\~japanese
		\~
		*/
		DirectP2PStartCondition_Jit,
		/**
		\~korean
		CNetServer.CreateP2PGroup �̳� CNetServer.JoinP2PGroup � ���� Ŭ���̾�Ʈ�� P2P ����� ���Ǵ� ������ ������
		Ȧ��Ī ������ �����Ѵ�. ���� ��� \ref super_peer  ���� ���� �Ǿ ���� �÷��� ���� ���� �ٲ�� �Ѵٸ� �̰���
		�ʿ��� ���� ���� ���̴�.

		\~english
		This forcefully begins hole-punching at the moment when P2P communication among clients is allowed by CNetServer.CreateP2PGroup or CNetServer.JoinP2PGroup or others.
		For an example, if there is a need to change super peer at \ref super_peer during game play, this may be needed.

		\~chinese
		�� CNetServer.CreateP2PGroup%��� CNetServer.JoinP2PGroup ����ʫ��?P2P������?����?�����?�����?������\ref super_peer%����??�������super peer��??ʦ�����??��

		\~japanese
		\~
		*/
		DirectP2PStartCondition_Always,
		DirectP2PStartCondition_LAST,
	};
	/**  @} */

	/**
	\~korean
	����� �Ǽ��� ���� ������ ProudNet�� �����ִ� ���

	\~english
	The way Proudnet shows error caused by user

	\~chinese
	ProudNet ?�����?����?������??��۰����

	\~japanese
	\~
	*/
	public enum WrapErrorReaction
	{
		/**
		\~korean
		��ȭ ���ڸ� �����ش�. ���� ���������� ��������� �������� ���忡���� Ǯ��ũ���� ��� ����¡���� ���� �� �־ �Ƿ� ���� ã�Ⱑ �� ����� �� �ִ�.

		\~english
		Shows chat box. This may be useful during development process but it can also be very troublesome since the chat box can be seen to end users as full screen freezing.

		\~chinese
		?��???��?�???����ު����驣�ӣ?����?��?���?��ʦ��??��?freezing��????ʦ�������ʥ��?��

		\~japanese
		\~
		*/
		ErrorReaction_MessageBox,
		/**
		\~korean
		ũ���ø� �����Ѵ�. �������� ���忡���� ũ���÷� ��Ÿ���Ƿ� ������� ��� ������ �� ���� ã�� �� �ִ�.
		��, \ref minidump  ���� ȥ���ؾ� �� ��ġ�� �ִ�.

		\~english
		Causes a crash. From end users' point of view, this is definitely a crash so it can be rather easier to find what the problem is when released.
		But, it is more effective when used along with \ref minidump.

		\~chinese
		??crash�����?��??��?crash��ʦ������?��release����ס�
		ӣ�����\ref minidump%���?������?��

		\~japanese
		\~
		*/
		ErrorReaction_AccessViolation,
		/**
		\~korean
		����� ���â������ �������ϴ�. ũ���ó� ��ȭ���ڸ� ����ٸ��� ��Ȳ�� �ƴ϶�� �̿ɼ��� ����Ͻʽÿ�.

		\~english
		It shows only debugger output screen. If you can not pop up crash or message box, please use this option.

		\~chinese
		��?���???��?������?��crash���???����?��?��?�����??��

		\~japanese
		\~
		*/
		ErrorReaction_DebugOutput,
		/**
		\~korean
		����� �극��ũ�� �̴ϴ�. �ش�ɼ��� ����� ��忡���� ����Ͻʽÿ�.
		\~english
		\~
		*/
		ErrorReaction_DebugBreak
	};

	/**
	\~korean
	���� ����

	\~english
	Operation type

	\~chinese
	?ߩ??��

	\~japanese
	\~
	*/
	public enum WrapValueOperType
	{
		/**
		\~korean
		����

		\~english
		Addition

		\~chinese
		ʥ����

		\~japanese
		\~
		*/
		ValueOperType_Plus,
		/**
		\~korean
		����

		\~english
		Subtraction

		\~chinese
		?��

		\~japanese
		\~
		*/
		ValueOperType_Minus,
		/**
		\~korean
		����

		\~english
		Multiplication

		\~chinese
		�����

		\~japanese
		\~
		*/
		ValueOperType_Multiply,
		/**
		\~korean
		������

		\~english
		Division

		\~chinese
		�����

		\~japanese
		\~
		*/
		ValueOperType_Division
	};

	/**
	\~korean
	�� ����

	\~english
	Comparison type

	\~chinese
	��???��

	\~japanese
	\~
	*/
	public enum WrapValueCompareType
	{
		/**
		\~korean
		ũ�ų� ������

		\~english
		Greater or equal

		\~chinese
		�������͡�

		\~japanese
		\~
		*/
		ValueCompareType_GreaterEqual,

		/**
		\~korean
		ũ��

		\~english
		Greater

		\~chinese
		����?��

		\~japanese
		\~
		*/
		ValueCompareType_Greater,

		/**
		\~korean
		�۰ų� ������

		\~english
		Less or equal

		\~chinese
		������͡�

		\~japanese
		\~
		*/
		ValueCompareType_LessEqual,

		/**
		\~korean
		������

		\~english
		Less

		\~chinese
		���?��

		\~japanese
		\~
		*/
		ValueCompareType_Less,

		/**
		\~korean
		������

		\~english
		Equal

		\~chinese
		���͡�

		\~japanese
		\~
		*/
		ValueCompareType_Equal,

		/**
		\~korean
		�ٸ���

		\~english
		Not equal

		\~chinese
		������?��

		\~japanese
		\~
		*/
		ValueCompareType_NotEqual
	};

	/**
	\~korean
	��ȣȭ ����

	\~english
	Encryption Level

	\~chinese
	ʥ�������

	\~japanese
	\~
	*/
	public enum WrapEncryptLevel
	{
		/**
		\~korean
		AES ��ȣȭ ���� ��

		\~english
		AES encryption level Low

		\~chinese
		AES ʥ������

		\~japanese
		\~
		*/
		EncryptLevel_Low = 128,
		/**
		\~korean
		AES ��ȣȭ ���� ��

		\~english
		AES encryption level Middle

		\~chinese
		AES ʥ������顣

		\~japanese
		\~
		*/
		EncryptLevel_Middle = 192,
		/**
		\~korean
		AES ��ȣȭ ���� ��

		\~english
		AES encryption level High

		\~chinese
		AES ʥ�����߾��

		\~japanese
		\~
		*/
		EncryptLevel_High = 256,
	};

	/**
	\~korean
	Fast ��ȣȭ ����

	\~english
	Fast encryption level

	\~chinese
	Fast ʥ�������

	\~japanese
	\~
	*/
	public enum WrapFastEncryptLevel
	{
		/**
		\~korean
		Fast ��ȣȭ ���� ��

		\~english
		Fast encryption level Low

		\~chinese
		Fastʥ������

		\~japanese
		\~
		*/
		FastEncryptLevel_Low = 512,
		/**
		\~korean
		Fast ��ȣȭ ���� ��

		\~english
		Fast encryption level Middle

		\~chinese
		Fastʥ������顣

		\~japanese
		\~
		*/
		FastEncryptLevel_Middle = 1024,
		/**
		\~korean
		Fast ��ȣȭ ���� ��

		\~english
		Fast encryption level High

		\~chinese
		Fastʥ�����߾��

		\~japanese
		\~
		*/
		FastEncryptLevel_High = 2048,
	};

	public enum WrapHostType
	{
		HostType_Server,
		HostType_Peer,
		HostType_All,
	};

	/**
	\~korean
	HostID ���� ��� �ɼ��Դϴ�.

	\~english
	It is an option for HostID reuse function.

	\~chinese
	HostID�����������??��

	\~japanese
	HostID�����Ѧ�����׫����Ǫ���

	\~
	*/
	public enum WrapHostIDGenerationPolicy
	{
		/**
		\~korean
		HostID ���� ����� ����մϴ�.
		-�⺻���Դϴ�.

		\~english
		It uses a HostID reuse function.
		-It is a default value.

		\~chinese
		HostID ���������������
		-?����?��.

		\~japanese
		HostID�����Ѧ�����Ū��ު���
		?�ǫի�������Ǫ�

		\~
		*/
		HostIDGenerationPolicy_Recycle = 1,

		/**
		\~korean
		HostID ���� ����� ������� �ʽ��ϴ�.

		\~english
		It does not use a HostID reuse function.

		\~chinese
		HostID �����������������.

		\~japanese
		HostID�����Ѧ�����Ū��ު���

		\~
		*/
		HostIDGenerationPolicy_NoRecycle,
	};

	/**
	\~korean
	������ ���Դϴ�.

	\~english
	Thread model.

	\~chinese
	?��ټ����

	\~japanese
	����ëɫ�ǫ�Ǫ���

	\~
	*/
	public enum WrapThreadModel
	{
		/**
		\~korean
		���� ������ ���Դϴ�. ����ڰ� ���� ������ ������ �۵����� �ǹ��մϴ�.
		���� �����尡 �����Ƿ� ����ڴ� Proud::CNetClient::FrameMove�� �ּ� �� 1/60�ʸ��� ���������� ȣ���� �־�� �մϴ�.

		\~english
		Single thread model. Runs code on threads created by user.
		As there is no networker thread, You must call Proud::CNetClient::FrameMove for every 1/60 seconds.

		\~chinese
		??��ټ����?�����??����?��򮡣
		���?��?ء��?���?������ 1/60 ��?̰�??�� Proud::CNetClient::FrameMove��

		\~japanese
		���󫰫뫹��ëɫ�ǫ�Ǫ�����?��?��������������ë�߾�����ª��몳�Ȫ���ګ���ު���
		ܬ�˫���ëɪ��ʪ����ᡢ��?��?��Proud :: CNetClient :: FrameMove�������1/60�����Ȫ�??�ܪ���������驪�����ު���

		\~
		*/
		ThreadModel_SingleThreaded = 1,

		/**
		\~korean
		��Ƽ ������ ���Դϴ�. Thread pool�� ���� ����� �� ������ �۵����� �ǹ��մϴ�.

		\~english
		Multi thread model. Runs code on the separated thread pool.

		\~chinese
		��?��ټ����???��?���??����߾��

		\~japanese
		�ޫ������ëɫ�ǫ�Ǫ��� Thread pool��ܬ?��������������߾�����ª��몳�Ȫ���ګ���ު���
		\~
		*/
		ThreadModel_MultiThreaded,

		/**
		\~korean
		���� ������ ���Դϴ�. ����ڰ� ���� Proud.CThreadPool ������ �۵����� �ǹ��մϴ�.

		\~english
		Use-external-thread model. Runs code on Proud.CThreadPool instance create by user.

		\~chinese
		��ݻ?��ټ����?�����??���� Proud.CThreadPool��

		\~japanese
		��?����ëɫ�ǫ�Ǫ�����?��?����������Proud.CThreadPool߾�����ª��몳�Ȫ���ګ���ު���

		\~
		*/
		ThreadModel_UseExternalThreadPool,
	};


	//������ ���ο� �ڵ� WrapCVariant �� ���� �� ���ֳ�
	enum WrapCVariant_Type
	{
		t_char,
		t_i64,
		t_int,
		t_short,
		t_string,
		t_float,
		t_double,
		t_datetime,
		t_guid,
	};
}