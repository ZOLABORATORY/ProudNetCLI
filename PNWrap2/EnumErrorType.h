#pragma once

//±×³É ¿ÜºÎ Æ÷ÆÃ¿ëÀ¸·Î º¹-ºÙ ÇÑ ÄÚµåÀÓ ÇÁ¶ó¿ìµå³İ ¿øº» ÄÚµå ÀÌ¸§¾Õ¿¡ Wrap ¸¸ ºÙÀÓ
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
		¸Å¿ì ³ôÀº ¿ì¼±¼øÀ§. connectivity test¸¦ À§ÇÑ ping µî¿¡ »ç¿ëµÊ. PN Àü¿ë

		\~english TODO:translate needed.

		\~chinese
		ŞªßÈÍÔîÜ?à»?ßí¡£ŞÅéÄî¤?Öõconnectivity testîÜpingÔõ¡£PN ?éÄ¡£

		\~japanese
		\~
		*/
		MessagePriority_Ring0 = 0,

		/**
		\~korean
		PN Àü¿ë

		\~english TODO:translate needed.

		\~chinese
		PN ?éÄ¡£

		\~japanese
		\~
		*/
		MessagePriority_Ring1,

		/**
		\~korean
		³ôÀº ¿ì¼±¼øÀ§

		\~english TODO:translate needed.

		\~chinese
		ÍÔîÜ?à»?ßí¡£

		\~japanese
		\~
		*/
		MessagePriority_High,

		/**
		\~korean
		º¸Åë ¿ì¼±¼øÀ§. °¡Àå ¸¹ÀÌ »ç¿ëµÊ.

		\~english TODO:translate needed.

		\~chinese
		ìéÚõ?à»?ßí¡£éÄîÜõÌÒı¡£

		\~japanese
		\~
		*/
		MessagePriority_Medium,

		/**
		\~korean
		³·Àº ¿ì¼±¼øÀ§

		\~english TODO:translate needed.

		\~chinese
		î¸îÜ?à»?ßí¡£

		\~japanese
		\~
		*/
		MessagePriority_Low,

		/**
		\~korean
		¸Å¿ì ³·Àº ¿ì¼±¼øÀ§
		PN Àü¿ë

		\~english TODO:translate needed.

		\~chinese
		ŞªßÈî¸îÜ?à»?ßí¡£
		PN ?éÄ¡£

		\~japanese
		\~
		*/
		MessagePriority_Ring99,

		/**
		\~korean
		»ç¿ëÀÚ´Â »ç¿ëÇÒ ¼ö ¾ø´Â °ª

		\~english TODO:translate needed.

		\~chinese
		éÄ?ÜôÒöŞÅéÄîÜ?¡£

		\~japanese
		\~
		*/
		MessagePriority_LAST,
	};

	// È¦ÆİÄª ÆĞÅ¶Àº ¸¹À» ¼ö ÀÖ´Ù. ÀÌ°ÍÀÌ Æ®·¡ÇÈÀ» ¹æÇØÇÏ¸é ¾ÈµÇ¹Ç·Î ¿ì¼±¼øÀ§¸¦ ÃÖÇÏÀ§·Î µĞ´Ù.
	static const WrapMessagePriority MessagePriority_Holepunch = MessagePriority_Ring99;

	// ÁÖÀÇ: ÀÌ°Íµµ ¹Ù²Ù¸é ProudClr namespaceÀÇ µ¿¸í ½Éº¼µµ ¼öÁ¤ÇØ¾ß ÇÑ´Ù.

	public enum WrapMessageReliability
	{
		MessageReliability_Unreliable = 0,
		MessageReliability_Reliable,
		MessageReliability_LAST,
	};

	// ÁÖÀÇ: ÀÌ°Íµµ ¹Ù²Ù¸é ProudClr namespaceÀÇ µ¿¸í ½Éº¼µµ ¼öÁ¤ÇØ¾ß ÇÑ´Ù.

	/**
	\~korean
	¿¡·¯ Å¸ÀÔ ÄÚµå

	\~english TODO:translate needed.

	\~chinese
	???úşÓÛ?¡£

	\~japanese
	\~
	*/
	public enum WrapErrorType
	{
		/**
		\~korean
		¼º°ø. ¹®Á¦ ¾øÀ½.

		\~english TODO:translate needed.

		\~chinese
		à÷Íí¡£?êó??¡£

		\~japanese
		\~
		*/
		ErrorType_Ok = 0,

		/**
		\~korean
		¿¹¿Ü »óÈ² ¹ß»ı

		\~english TODO:translate needed.

		\~chinese
		?ßæÖÇèâï×?¡£

		\~japanese
		\~
		*/
		ErrorType_Unexpected,

		/**
		\~korean
		ÀÌ¹Ì ¿¬°áµÇ¾î ÀÖÀ½

		\~english TODO:translate needed.

		\~chinese
		ì«?ãÀ?ïÈ??
		\~japanese
		\~
		*/
		ErrorType_AlreadyConnected,

		/**
		\~korean
		TCP ¿¬°á ½ÇÆĞ

		\~english TODO:translate needed.

		\~chinese
		TCP ?ïÈã÷?¡£

		\~japanese
		\~
		*/
		ErrorType_TCPConnectFailure,

		/**
		\~korean
		Àß¸øµÈ ´ëÄªÅ°

		\~english TODO:translate needed.

		\~chinese
		??îÜ??key¡£

		\~japanese
		\~
		*/
		ErrorType_InvalidSessionKey,

		/**
		\~korean
		¾ÏÈ£È­°¡ ½ÇÆĞÇßÀ½

		\~english TODO:translate needed.

		\~chinese
		Ê¥ÚËã÷?¡£

		\~japanese
		\~
		*/
		ErrorType_EncryptFail,

		/**
		\~korean
		ÇØÄ¿°¡ ±úÁø µ¥ÀÌÅÍ¸¦ Àü¼ÛÇß°Å³ª º¹È£È­°¡ ½ÇÆĞÇßÀ½

		\~english TODO:translate needed.

		\~chinese
		ıÙËÔÊ¦Òö?áêÖõ???Ëß£¬ûäíºãÀú°?ã÷?¡£

		\~japanese
		\~
		*/
		ErrorType_DecryptFail,

		/**
		\~korean
		¼­¹ö ¿¬°á °úÁ¤ÀÌ ³Ê¹« ¿À·¡ °É·Á¼­ ½ÇÆĞ Ã³¸®µÊ

		\~english TODO:translate needed.

		\~chinese
		ì×Ü×?Ğï?ïÈ????ì»ã÷?¡£

		\~japanese
		\~
		*/
		ErrorType_ConnectServerTimeout,

		/**
		\~korean
		¼­¹ö ¿¬°áÀ» À§ÇÑ ÇÁ·ÎÅäÄİ ¹öÀüÀÌ ´Ù¸§

		\~english TODO:translate needed.

		\~chinese
		Ü×?Ğï?ïÈîÜ????÷úÜâÜôÔÒ¡£

		\~japanese
		\~
		*/
		ErrorType_ProtocolVersionMismatch,

		/**
		\~korean
		¼­¹ö°¡ ¿¬°áÀ» ÀÇµµÀûÀ¸·Î °ÅºÎÇßÀ½

		\~english TODO:translate needed.

		\~chinese
		Ü×?ĞïÍºëòËŞ??ïÈ¡£

		\~japanese
		\~
		*/
		ErrorType_NotifyServerDeniedConnection,

		/**
		\~korean
		¼­¹ö ¿¬°á ¼º°ø!

		\~english TODO:translate needed.

		\~chinese
		Ü×?Ğï?ïÈà÷Íí£¡

		\~japanese
		\~
		*/
		ErrorType_ConnectServerSuccessful,

		/**
		\~korean
		»ó´ëÃø È£½ºÆ®¿¡¼­ ¿¬°áÀ» ÇØÁ¦ÇßÀ½

		\~english TODO:translate needed.

		\~chinese
		?Û°ñ«Ïõú°ğ¶Öõ?ïÈ¡£

		\~japanese
		\~
		*/
		ErrorType_DisconnectFromRemote,

		/**
		\~korean
		ÀÌÂÊ È£½ºÆ®¿¡¼­ ¿¬°áÀ» ÇØÁ¦ÇßÀ½

		\~english TODO:translate needed.

		\~chinese
		??ñ«Ïõú°ğ¶Öõ?ïÈ¡£

		\~japanese
		\~
		*/
		ErrorType_DisconnectFromLocal,

		/**
		\~korean
		À§ÇèÇÑ »óÈ²À» ºÒ·¯¿Ã ¼ö ÀÖ´Â ÀÎÀÚ°¡ ÀÖÀ½

		\~english TODO:translate needed.

		\~chinese
		ğíî¤Ê¦ÒöìÚÑÃêË???îÜì×áÈ¡£

		\~japanese
		\~
		*/
		ErrorType_DangerousArgumentWarning,

		/**
		\~korean
		¾Ë ¼ö ¾ø´Â ÀÎÅÍ³İ ÁÖ¼Ò

		\~english TODO:translate needed.

		\~chinese
		Ú±ò±îÜû»??ò¢ò£¡£

		\~japanese
		\~
		*/
		ErrorType_UnknownAddrPort,

		/**
		\~korean
		¼­¹ö ÁØºñ ºÎÁ·

		\~english TODO:translate needed.

		\~chinese
		Ü×?Ğïñ×?Üôğë¡£

		\~japanese
		\~
		*/
		ErrorType_ServerNotReady,

		/**
		\~korean
		¼­¹ö ¼ÒÄÏÀÇ listenÀ» ½ÃÀÛÇÒ ¼ö ¾ø½À´Ï´Ù. TCP ¶Ç´Â UDP ¼ÒÄÏÀÌ ÀÌ¹Ì »ç¿ëÁßÀÎ Æ÷Æ®ÀÎÁö È®ÀÎÇÏ½Ê½Ã¿À.

		\~english TODO:translate needed.

		\~chinese
		ÙéÛö?ã·Ü×?ĞïsocketîÜlisten¡£???TCPûäíºUDPsocketãÀÜúì«ãÀŞÅéÄñéîÜÓ®Ï¢¡£

		\~japanese
		\~
		*/
		ErrorType_ServerPortListenFailure,

		/**
		\~korean
		ÀÌ¹Ì °³Ã¼°¡ Á¸ÀçÇÕ´Ï´Ù.

		\~english TODO:translate needed.

		\~chinese
		?ßÚì«ğíî¤¡£

		\~japanese
		\~
		*/
		ErrorType_AlreadyExists,

		/**
		\~korean
		Á¢±ÙÀÌ °ÅºÎµÇ¾ú½À´Ï´Ù.
		- \ref dbc2_nonexclusive_overview ±â´É¿¡¼­, DB cache server°¡ ºñµ¶Á¡Àû Á¢±Ù ±â´ÉÀ» ¾²Áö ¾Ê°Ú´Ù´Â ¼³Á¤ÀÌ µÇ¾î ÀÖÀ¸¸é ¹ß»ıÇÒ ¼ö ÀÖ½À´Ï´Ù.
		- À©µµ¿ì ºñ½ºÅ¸ÀÌ»óÀÇ OS¿¡¼­ °ü¸®ÀÚ±ÇÇÑÀÌ ¾øÀÌ CNetUtil::EnableTcpOffload( bool enable ) ÇÔ¼ö°¡ È£ÃâµÇ¸é ¹ß»ıÇÒ ¼ö ÀÖ½À´Ï´Ù.

		\~english
		Access denied.
		- At \ref dbc2_nonexclusive_overview function, it could occur if a function that DB cache server does not use exclusive access function has been set.
		- At OS over window vista, It could occur when CNetUtil::EnableTcpOffload( bool enable ) function is called without administration authority.

		\~chinese
		ïÈĞÎù¬ËŞ?¡£
		- î¤\ref dbc2_nonexclusive_overview%ÍíÒöß¾£¬åıÍıDB cache serverù¬?öÇà÷ÜôŞÅéÄÍìú½ïÈĞÎÍíÒöîÜ?øµ??ßæó®??¡£
		- î¤window£¬vista ì¤ß¾îÜOSñé£¬?êóÎ·×â??ùÚû¼õó CNetUtil::EnableTcpOffload ( bool enable )ùŞ?îÜ?£¬Ê¦Òö??ßæó®??¡£

		\~japanese
		ïÈĞÎª¬ËŞÜúªµªìªŞª·ª¿¡£
		- \ref dbc2_nonexclusive_overview Ñ¦ÒöªÇ, DB cache serverª¬Şª?ï¿îÜïÈĞÎÑ¦ÒöªòŞÅéÄª·ªÊª¤ªÈàâïÒªµªìªÆª¤ªëªÈ?ßæª¹ªëÊ¦Òöàõª¬ª¢ªêªŞª¹¡£
		- Window Vistaì¤ß¾ªÎOSªÇÎ·×âíº?ùÚªÊª·ªË CNetUtil::EnableTcpOffload( bool enable ) ??ª¬û¼ªÓõóªµªìªëªÈ?ßæª¹ªëÊ¦Òöàõª¬ª¢ªêªŞª¹¡£

		\~
		*/
		ErrorType_PermissionDenied,

		/**
		\~korean
		Àß¸øµÈ session GuidÀÔ´Ï´Ù.

		\~english TODO:translate needed.

		\~chinese
		??îÜsession Guid¡£

		\~japanese
		\~
		*/
		ErrorType_BadSessionGuid,

		/**
		\~korean
		Àß¸øµÈ credentialÀÔ´Ï´Ù.

		\~english TODO:translate needed.

		\~chinese
		??îÜcredential¡£

		\~japanese
		\~
		*/
		ErrorType_InvalidCredential,

		/**
		\~korean
		Àß¸øµÈ hero nameÀÔ´Ï´Ù.

		\~english TODO:translate needed.

		\~chinese
		??îÜhero name¡£

		\~japanese
		\~
		*/
		ErrorType_InvalidHeroName,

		/**
		\~korean
		·Îµù °úÁ¤ÀÌ unlock ÈÄ lock ÇÑ ÈÄ ²¿ÀÓÀÌ ¹ß»ıÇß´Ù

		\~english TODO:translate needed.

		\~chinese
		Ê¥??ïïunlockì¤ı¨£¬lock ı¨?ßæéöó¢¡£

		\~japanese
		\~
		*/
		ErrorType_LoadDataPreceded,

		/**
		\~korean
		Ãâ·Â ÆÄ¶ó¸ŞÅÍ AdjustedGamerIDNotFilled°¡ Ã¤¿öÁöÁö ¾Ê¾Ò½À´Ï´Ù.

		\~english TODO:translate needed.

		\~chinese
		?õó??AdjustedGamerIDNotFilled?êóù¬?õö¡£

		\~japanese
		\~
		*/
		ErrorType_AdjustedGamerIDNotFilled,

		/**
		\~korean
		ÇÃ·¹ÀÌ¾î Ä³¸¯ÅÍ°¡ Á¸ÀçÇÏÁö ¾Ê½À´Ï´Ù.

		\~english TODO:translate needed.

		\~chinese
		èÌÊ«ÊÇßäÜôğíî¤¡£

		\~japanese
		\~
		*/
		ErrorType_NoHero,

		/**
		\~korean
		À¯´Ö Å×½ºÆ® ½ÇÆĞ

		\~english
		Unit test failed

		\~chinese
		?êª??ã÷?¡£

		\~japanese
		\~
		*/
		ErrorType_UnitTestFailed,

		/**
		\~korean
		peer-to-peer UDP Åë½ÅÀÌ ¸·Çû½À´Ï´Ù.

		\~english TODO:translate needed.

		\~chinese
		peer-to-peer UDP ÷×ãáÓòßİ¡£

		\~japanese
		\~
		*/
		ErrorType_P2PUdpFailed,

		/**
		\~korean
		P2P reliable UDP°¡ ½ÇÆĞÇß½À´Ï´Ù.

		\~english TODO:translate needed.

		\~chinese
		P2P reliable UDPã÷?¡£

		\~japanese
		\~
		*/
		ErrorType_ReliableUdpFailed,

		/**
		\~korean
		Å¬¶óÀÌ¾ğÆ®-¼­¹ö UDP Åë½ÅÀÌ ¸·Çû½À´Ï´Ù.

		\~english TODO:translate needed.

		\~chinese
		èÌÊ«-Ü×?ĞïîÜUDP÷×ãáÓòßİ¡£

		\~japanese
		\~
		*/
		ErrorType_ServerUdpFailed,

		/**
		\~korean
		´õ ÀÌ»ó °°ÀÌ ¼Ò¼ÓµÈ P2P ±×·ìÀÌ ¾ø½À´Ï´Ù.

		\~english TODO:translate needed.

		\~chinese
		î¢?êóìéÔÒá¶?îÜP2P?¡£

		\~japanese
		\~
		*/
		ErrorType_NoP2PGroupRelation,

		/**
		\~korean
		»ç¿ëÀÚ Á¤ÀÇ ÇÔ¼ö(RMI ¼ö½Å ·çÆ¾ È¤Àº ÀÌº¥Æ® ÇÚµé·¯)¿¡¼­ exceptionÀÌ throwµÇ¾ú½À´Ï´Ù.

		\~english TODO:translate needed.

		\~chinese
		?éÄ?ïÒ?ùŞ?£¨RMI â¥ãáÖÇïïûäíºŞÀËìhandler£©exception ù¬throw¡£

		\~japanese
		\~
		*/
		ErrorType_ExceptionFromUserFunction,

		/**
		\~korean
		»ç¿ëÀÚÀÇ ¿äÃ»¿¡ ÀÇÇÑ ½ÇÆĞÀÔ´Ï´Ù.

		\~english TODO:translate needed.

		\~chinese
		éÄ?é­?ğãà÷îÜã÷?¡£

		\~japanese
		\~
		*/
		ErrorType_UserRequested,

		/**
		\~korean
		Àß¸øµÈ ÆĞÅ¶ Çü½ÄÀÔ´Ï´Ù. »ó´ëÃø È£½ºÆ®°¡ ÇØÅ·µÇ¾ú°Å³ª ¹ö±×ÀÏ ¼ö ÀÖ½À´Ï´Ù.

		\~english TODO:translate needed.

		\~chinese
		??îÜ?ËßøĞû¡ãÒ¡£Ê¦ÒöãÀ?Û°ñ«Ïõù¬ıÙûäíºãÀğíî¤×©Ô×¡£

		\~japanese
		\~
		*/
		ErrorType_InvalidPacketFormat,

		/**
		\~korean
		³Ê¹« Å« Å©±âÀÇ ¸Ş½ÃÂ¡ÀÌ ½ÃµµµÇ¾ú½À´Ï´Ù. ±â¼úÁö¿øºÎ¿¡ ¹®ÀÇÇÏ½Ê½Ã¿À. ÇÊ¿ä½Ã \ref message_length  ¸¦ Âü°íÇÏ½Ê½Ã¿À.

		\~english TODO:translate needed.

		\~chinese
		??ŞÅéÄÖõ?ÓŞîÜmessaging¡£?íª?Ğü?ò¨êµİ»¡£ù±é©???ÍÅ\ref message_length%¡£

		\~japanese
		\~
		*/
		ErrorType_TooLargeMessageDetected,

		/**
		\~korean
		Unreliable ¸Ş¼¼Áö´Â encrypt ÇÒ¼ö ¾ø½À´Ï´Ù.

		\~english TODO:translate needed.

		\~chinese
		Unreliable ãáãÓÜôÒöencrypt¡£

		\~japanese
		\~
		*/
		ErrorType_CannotEncryptUnreliableMessage,

		/**
		\~korean
		Á¸ÀçÇÏÁö ¾Ê´Â °ªÀÔ´Ï´Ù.

		\~english TODO:translate needed.

		\~chinese
		Üôğíî¤îÜ?¡£

		\~japanese
		\~
		*/
		ErrorType_ValueNotExist,

		/**
		\~korean
		Å¸ÀÓ¾Æ¿ô ÀÔ´Ï´Ù.

		\~english TODO:translate needed.

		\~chinese
		õ±?¡£

		\~japanese
		\~
		*/
		ErrorType_TimeOut,

		/**
		\~korean
		·ÎµåµÈ µ¥ÀÌÅÍ¸¦ Ã£À»¼ö ¾ø½À´Ï´Ù.

		\~english TODO:translate needed.

		\~chinese
		ÙéÛö?ÓğÊ¥?îÜ?Ëß¡£

		\~japanese
		\~
		*/
		ErrorType_LoadedDataNotFound,

		/**
		\~korean
		\ref send_queue_heavy . ¼Û½Å queue°¡ Áö³ªÄ¡°Ô Ä¿Á³½À´Ï´Ù.

		\~english TODO:translate needed.

		\~chinese
		\ref send_queue_heavy¡£?áêqueue?ÓŞ¡£

		\~japanese
		\~
		*/
		ErrorType_SendQueueIsHeavy,

		/**
		\~korean
		Heartbeat°¡ Æò±ÕÀûÀ¸·Î ³Ê¹« ´À¸²

		\~english TODO:translate needed.

		\~chinese
		Heartbeat øÁĞ³÷¼Ø·¡£

		\~japanese
		\~
		*/
		ErrorType_TooSlowHeartbeatWarning,

		/**
		\~korean
		¸Ş½ÃÁö ¾ĞÃàÀÌ ½ÇÆĞ ÇÏ¿´½À´Ï´Ù.

		\~english TODO:translate needed.

		\~chinese
		ãáãÓ??ã÷?¡£

		\~japanese
		\~
		*/
		ErrorType_CompressFail,

		/**
		\~korean
		Å¬¶óÀÌ¾ğÆ® ¼ÒÄÏÀÇ listenÀ» ½ÃÀÛÇÒ ¼ö ¾ø½À´Ï´Ù. TCP ¶Ç´Â UDP ¼ÒÄÏÀÌ ÀÌ¹Ì »ç¿ëÁßÀÎ Æ÷Æ®ÀÎÁö È®ÀÎÇÏ½Ê½Ã¿À.

		\~english
		Unable to start listening of client socket. Must check if either TCP or UDP socket is already in use.

		\~chinese
		ÙéÛö?ã·èÌÊ«socketîÜlisten¡£???TCPûäíºUDP socketÓ®Ï¢ãÀÜúì«î¤ŞÅéÄñé¡£

		\~japanese
		\~
		*/
		ErrorType_LocalSocketCreationFailed,

		/**
		\~korean
		SocketÀ» »ı¼ºÇÒ ¶§ Port Pool ³» port number·ÎÀÇ bind°¡ ½ÇÆĞÇß½À´Ï´Ù. ´ë½Å ÀÓÀÇÀÇ port number°¡ »ç¿ëµÇ¾ú½À´Ï´Ù. Port PoolÀÇ °¹¼ö°¡ ÃæºĞÇÑÁö È®ÀÎÇÏ½Ê½Ã¿ä.

		\~english
		Failed binding to local port that defined in Port Pool. Please check number of values in Port Pool are sufficient.

		\~chinese
		ßæà÷socketîÜ?ı¦èÙPort Pool?port numberîÜbindã÷?¡£ìòëòport numberù¬ÓÛôğŞÅéÄ¡£???Port PoolîÜ??ãÀÜúõöİÂ¡£

		\~japanese
		\~
		*/
		Error_NoneAvailableInPortPool,

		/**
		\~korean
		Port pool ³» °ªµé Áß ÇÏ³ª ÀÌ»óÀÌ Àß¸øµÇ¾ú½À´Ï´Ù. Æ÷Æ®¸¦ 0(ÀÓÀÇ Æ÷Æ® ¹ÙÀÎµù)À¸·Î ÇÏ°Å³ª Áßº¹µÇÁö ¾Ê¾Ò´ÂÁö È®ÀÎÇÏ½Ê½Ã¿ä.

		\~english
		Range of user defined port is wrong. Set port to 0(random port binding) or check if it is overlaped.

		\~chinese
		Port pool ñéìé?ì¤ß¾îÜ??õó?¡£??÷êÓ®Ï¢??0£¨ìòëòÓ®Ï¢binding£©ûäíºãÀÜúñì?¡£

		\~japanese
		\~
		*/
		ErrorType_InvalidPortPool,

		/**
		\~korean
		À¯È¿ÇÏÁö ¾ÊÀº HostID °ªÀÔ´Ï´Ù.

		\~english
		Invalid HostID.

		\~chinese
		ÙéüùîÜHostID¡£

		\~japanese
		\~
		*/
		ErrorType_InvalidHostID, // CODEREV-FORCERELAY: enum ErrorType¿¡ º¯°æÀ» °¡ÇÏ¼Ì±º¿ä. ÀÌ·¯ÇÑ °æ¿ì TypeToString_Kor, TypeToString_Eng,TypeToString_Chn¿¡µµ º¯°æÀ» °¡ÇØ¾ß ÇÕ´Ï´Ù. C#,AS,Java¹öÀü¿¡¼­µµ ¸¶Âù°¡ÁöÀÔ´Ï´Ù.

								 /**
								 \~korean
								 »ç¿ëÀÚ°¡ ¼ÒÈ­ÇÏ´Â ¸Ş½ÃÁö Ã³¸® ¼Óµµº¸´Ù ³»ºÎÀûÀ¸·Î ½×ÀÌ´Â ¸Ş½ÃÁöÀÇ ¼Óµµ°¡ ´õ ³ô½À´Ï´Ù.
								 Áö³ªÄ¡°Ô ³Ê¹« ¸¹Àº ¸Ş½ÃÁö¸¦ ¼Û½ÅÇÏ·Á°í Çß´ÂÁö, È¤Àº »ç¿ëÀÚÀÇ ¸Ş½ÃÁö ¼ö½Å ÇÔ¼ö°¡ Áö³ªÄ¡°Ô ´À¸®°Ô ÀÛµ¿ÇÏ°í ÀÖ´ÂÁö È®ÀÎÇÏ½Ê½Ã¿À.

								 \~english
								 The speed of stacking messages are higher than the speed of processing them.
								 Check that you are sending too many messages, or your message processing routines are running too slowly.

								 \~chinese
								 á¼ãÓîÜ÷Ø?áÜÓøÍÔéÍ?×â??îÜáÜÓø¡£
								 ???é©?áêîÜ?Ëì÷¼Òı£¬ûäá¼ãÓ?×âïïßí?ú¼?Ø·¡£
								 \~
								 \~
								 */
		ErrorType_MessageOverload,


		/** Accessing database failed. For example, query statement execution failed. You may see the details from comment variable.
		*/
		ErrorType_DatabaseAccessFailed,

		/**
		\~korean ¸Ş¸ğ¸®°¡ ºÎÁ·ÇÕ´Ï´Ù.

		\~english Out of memory.

		\~chinese ?ğíÜôğë.

		\~japanese «á«â«ê?ª¬ğëªêªŞª»ªó¡£
		\~
		*/
		ErrorType_OutOfMemory,

		/** ¼­¹ö¿ÍÀÇ ¿¬°áÀÌ ²÷¾îÁ®¼­ ¿¬°á º¹±¸ ±â´ÉÀÌ °¡µ¿µÇ¾úÁö¸¸, ÀÌ°Í ¸¶Àúµµ ½ÇÆĞÇß½À´Ï´Ù. */
		ErrorType_AutoConnectionRecoveryFailed,
	};

	/**
	\~korean
	ProudNet È£½ºÆ® ½Äº°ÀÚ

	\~english TODO:translate needed.

	\~chinese
	ProudNet ñ«Ïõ??íº¡£

	\~japanese
	\~
	*/
	public enum WrapHostID
	{
		/**
		\~korean
		¾øÀ½

		\~english
		None

		\~chinese
		Ùé

		\~japanese
		\~
		*/
		HostID_None = 0,

		/**
		\~korean
		¼­¹ö

		\~english
		Server

		\~chinese
		Ü×?Ğï

		\~japanese
		\~
		*/
		HostID_Server = 1,

		/**
		\~korean
		(»ç¿ë±İÁö)

		\~english
		(Do not use it)

		\~chinese
		£¨Ğ×ò­ŞÅéÄ£©

		\~japanese
		\~
		*/
		HostID_Last = 2
	};

	public enum Wrap_RmiID
	{
		RmiID_None = 0,
		RmiID_Last = 65535, // marmalade¿¡¼­ RMI ID°¡ word°¡ µÊÀ» º¸ÀåÇÏ±â À§ÇØ.
	};

	/** \~korean ¸ğµâ ³»¿¡¼­ ¹ß»ıÇÏ´Â ·Î±×ÀÇ ¹üÁÖ Å¸ÀÔÀÔ´Ï´Ù.
	\~english It is a category type of the log occurred within the module.
	\~chinese î¤Ù¼???ßæîÜLogÛõ??
	\~japanese «â«¸«å?«ë?ªÇ?ßæª¹ªë«í«°ªÎ«««Æ«´«ê?«¿«¤«×ªÇª¹¡£
	\~ */
	public enum WrapLogCategory
	{
		/** \~korean ±âº» ½Ã½ºÅÛ
		\~english Basic System
		\~chinese Ğñ?Í§?
		\~japanese ĞñÜâ«·«¹«Æ«à
		\~ */
		LogCategory_System,
		/** \~korean TCP Åë½Å °ü·Ã
		\~english Relevant to TCP communication
		\~chinese ßÓ? TCP ÷×ãá
		\~japanese TCP÷×ãá?Ö§
		\~ */
		LogCategory_Tcp,
		/** \~korean UDP Åë½Å °ü·Ã
		\~english Relevant to UDP communication
		\~chinese ßÓ? UDP ÷×ãá
		\~japanese UDP÷×ãá?Ö§
		\~ */
		LogCategory_Udp,
		/** \~korean P2P Åë½Å °ü·Ã
		\~english Relevant to P2P communication
		\~chinese ßÓ? P2P ÷×ãá
		\~japanese P2P÷×ãá?Ö§
		\~ */
		LogCategory_P2P
	};

	/**
	\~korean
	ÇØÅ·ÀÇ Á¾·ù

	\~english
	Type of hacking

	\~chinese
	ıÙËÔîÜ??¡£

	\~japanese
	\~
	*/
	public enum WrapHackType
	{
		/**
		\~korean
		ÇØÅ· ¾Æ´Ô

		\~english
		No hacking

		\~chinese
		ÜôãÀıÙËÔ¡£

		\~japanese
		\~
		*/
		HackType_None,

		/**
		\~korean
		½ºÇÇµåÇÙ

		\~english
		Speek hack

		\~chinese
		áÜÓøhack¡£

		\~japanese
		\~
		*/
		HackType_SpeedHack,

		/**
		\~korean
		ÆĞÅ¶ Á¶ÀÛ

		\~english
		Handle packet

		\~chinese
		?ËßøĞğÃíÂ¡£

		\~japanese
		\~
		*/
		HackType_PacketRig,
	};

	/**
	\~korean
	Å¸ È£½ºÆ®¿ÍÀÇ ¿¬°á »óÅÂ

	\~english
	Connection status with other hosts

	\~chinese
	?Ğìöâñ«ÏõîÜ?ïÈ??¡£

	\~japanese
	\~
	*/
	public enum WrapConnectionState
	{
		/**
		\~korean
		¿¬°áÀÌ ²÷¾îÁø »óÅÂ

		\~english
		Disconnected condition

		\~chinese
		?ïÈñé?îÜ??¡£

		\~japanese
		\~
		*/
		ConnectionState_Disconnected,

		/**
		\~korean
		¿¬°á ½Ãµµ¸¦ ÇßÁö¸¸ ¾ÆÁ÷ °á°ú¸¦ ¾Ë ¼ö ¾ø´Â »óÅÂ

		\~english
		Tried connecting but result is unknown

		\~chinese
		?ì«???ïÈ£¬Ó£ÙéÛöò±Ô³?ÍıîÜ??¡£

		\~japanese
		\~
		*/
		ConnectionState_Connecting,

		/**
		\~korean
		¿¬°á °úÁ¤ÀÌ ¼º°øÇÑ »óÅÂ

		\~english
		Succeed to connect

		\~chinese
		?ïÈ?ïïà÷ÍíîÜ??¡£

		\~japanese
		\~
		*/
		ConnectionState_Connected,

		/**
		\~korean
		¿¬°á ÇØÁ¦ °úÁ¤ÀÌ ÁøÇàÁßÀÎ »óÅÂ

		\~english
		Disconnecting is in progress

		\~chinese
		î¤?ú¼?ïÈú°ğ¶?ïïîÜ??¡£

		\~japanese
		\~
		*/
		ConnectionState_Disconnecting,
	};

	/**
	\~korean
	TCP fallbackÀ» ÀÇµµÀûÀ¸·Î ½ÃÇàÇÒ ¶§ÀÇ ¹æ¹ı

	\~english
	How to intentially use TCP fallback

	\~chinese
	Íºëò?ú¼TCP fallback?îÜÛ°Ûö¡£

	\~japanese
	\~
	*/
	public enum WrapFallbackMethod // °­µµ°¡ ³·Àº ¼øÀ¸·Î enum °ªÀ» Á¤·ÄÇÒ °Í
	{
		/**
		\~korean
		FallbackÀ» ¾ÈÇÔ. Áï ¼­¹ö ¹× peer¿ÍÀÇ UDP Åë½ÅÀ» ¸ğµÎ »ç¿ëÇÔ.

		\~english
		No Fallback. In other words, UDP communication to both server and peer are in use.

		\~chinese
		Üôñ®Fallback¡£?ŞÅéÄîïİ»îÜÜ×?ĞïĞà?peerîÜUDP÷×ãá¡£

		\~japanese
		\~
		*/
		FallbackMethod_None,
		/**
		\~korean
		¼­¹ö¿ÍÀÇ UDP Åë½ÅÀº À¯ÁöÇÏµÇ Å¸ Peerµé°úÀÇ UDP Åë½Å¸¸ÀÌ Â÷´ÜµÈ °ÍÀ¸·Î Ã³¸®ÇÑ´Ù. ÀÏ½ÃÀû Æ÷Æ®¸ÅÇÎ ½ÇÆĞ¿Í À¯»çÇÑ »óÈ²À» ÀçÇöÇÑ´Ù. °¡Àå °­µµ°¡ ³·´Ù.

		\~english
		Regards that UDP with server is sustained but UDP with other peers to be disconnected. Reproduce a circumstance similar to a temporary port mapping failure. This is the lowest option with weakest impact.

		\~chinese
		?ò¥?Ü×?ĞïîÜUDP÷×ãá£¬?×â?ñş?ĞìöâpeerîÜUDP÷×ãáñé?¡£î¢?ìé?îÜÓ®Ï¢ç±ßÀã÷?ûú?ŞÄîÜï×?¡£Ë­ÓøõÌî¸¡£

		\~japanese
		\~
		*/
		FallbackMethod_PeersUdpToTcp,
		/**
		\~korean
		¼­¹ö¿ÍÀÇ UDP Åë½ÅÀ» Â÷´ÜµÈ °ÍÀ¸·Î Ã³¸®ÇÑ´Ù. ÀÏ½ÃÀû Æ÷Æ®¸ÅÇÎ ½ÇÆĞ¿Í À¯»çÇÑ »óÈ²À» ÀçÇöÇÑ´Ù. ¾Æ¿ï·¯ Peerµé°úÀÇ UDP Åë½Åµµ Â÷´ÜµÈ´Ù. Áß°£ °­µµ´Ù.

		\~english
		Regards that UDP with server is disconnected. Reproduce a circumstance similar to a temporary port mapping failure. On top of that, it also disconnects UDP with peers. Intermediate impact.


		\~chinese
		?×â?ñş?ĞìöâpeerîÜUDP÷×ãáñé?¡£î¢?ìé?îÜÓ®Ï¢ç±ßÀã÷?ûú?ŞÄîÜï×?¡£?peerîÜUDP÷×ãáå¥ù¬ñé?¡£Ë­ÓøìéÚõ¡£

		\~japanese
		\~
		*/
		FallbackMethod_ServerUdpToTcp,
		/**
		\~korean
		Å¬¶óÀÌ¾ğÆ®ÀÇ UDP ¼ÒÄÏÀ» ¾Æ¿¹ ´İ¾Æ¹ö¸°´Ù. ¿µ±¸ÀûÀÎ UDP º¹±¸¸¦ ¸øÇÏ°Ô ÇÑ´Ù. °¡Àå °­µµ°¡ ³ô´Ù.
		- Proud.CNetServer.SetDefaultFallbackMethod ¿¡¼­´Â »ç¿ëÇÒ ¼ö ¾ø´Ù.

		\~english
		All UDP sockets of client will be shut down. UDP restoration will never be possible. Strongest impact.
		- Unable to use in Proud.CNetServer.SetDefaultFallbackMethod

		\~chinese
		òÁïÈ??èÌÊ«îÜUDPsocket¡£Üô?ñ®çµÎùàõîÜUDPáó?¡£Ë­ÓøõÌÍÔ¡£

		\~japanese
		\~
		*/
		FallbackMethod_CloseUdpSocket,
	};

	/**
	\~korean
	Å¬¶óÀÌ¾ğÆ®°£ Á÷Á¢ P2P Åë½ÅÀ» À§ÇÑ È¦ÆİÄªÀ» ½ÃÀÛÇÏ´Â Á¶°Ç

	\~english
	Conditions to start hole-punching for direct P2P communication among clients

	\~chinese
	?ÖõèÌÊ«ñı??ã·òÁïÈP2P÷×ãáîÜöèÔ×?Ëì¡£

	\~japanese
	\~
	*/
	public enum WrapDirectP2PStartCondition
	{
		/**
		\~korean
		²À ÇÊ¿äÇÑ »óÈ²ÀÌ ¾Æ´Ñ ÀÌ»ó È¦ÆİÄªÀ» ÇÏÁö ¾Ê´Â´Ù. À¢¸¸ÇÏ¸é ÀÌ°ÍÀ» ¾²´Â °ÍÀÌ ÁÁ´Ù.

		\~english
		Unless really needed, it is recommended not to do hole-punching. Using this is strongly recommended.

		\~chinese
		ÜôãÀù±é©îÜï×?îÜ?Üô?ú¼öèÔ×¡£õÌû¿éÄ??¡£

		\~japanese
		\~
		*/
		DirectP2PStartCondition_Jit,
		/**
		\~korean
		CNetServer.CreateP2PGroup ÀÌ³ª CNetServer.JoinP2PGroup µî¿¡ ÀÇÇØ Å¬¶óÀÌ¾ğÆ®°£ P2P Åë½ÅÀÌ Çã¿ëµÇ´Â ¼ø°£¿¡ ¹«Á¶°Ç
		È¦ÆİÄª °úÁ¤À» ½ÃÀÛÇÑ´Ù. ¿¹¸¦ µé¾î \ref super_peer  ¿¡¼­ ¼öÆÛ ÇÇ¾î¸¦ °ÔÀÓ ÇÃ·¹ÀÌ µµÁß Á¾Á¾ ¹Ù²ã¾ß ÇÑ´Ù¸é ÀÌ°ÍÀÌ
		ÇÊ¿äÇÒ ¼öµµ ÀÖÀ» °ÍÀÌ´Ù.

		\~english
		This forcefully begins hole-punching at the moment when P2P communication among clients is allowed by CNetServer.CreateP2PGroup or CNetServer.JoinP2PGroup or others.
		For an example, if there is a need to change super peer at \ref super_peer during game play, this may be needed.

		\~chinese
		ù¬ CNetServer.CreateP2PGroup%ûäíº CNetServer.JoinP2PGroup £¬èÌÊ«ñı?P2P÷×ãáëÃ?îÜâë?ìéïÒé©?ã·öèÔ×?ïï¡£ÖÇåıî¤\ref super_peer%£¬êı??ú¼ñéé©÷êsuper peerËÇ??Ê¦ÒöâÍé©??¡£

		\~japanese
		\~
		*/
		DirectP2PStartCondition_Always,
		DirectP2PStartCondition_LAST,
	};
	/**  @} */

	/**
	\~korean
	»ç¿ëÀÚ ½Ç¼ö·Î ÀÎÇÑ ¿¡·¯¸¦ ProudNetÀÌ º¸¿©ÁÖ´Â ¹æ¹ı

	\~english
	The way Proudnet shows error caused by user

	\~chinese
	ProudNet ?ãÆë¦éÄ?îÜã÷?ğãà÷îÜ??îÜÛ°Ûö¡£

	\~japanese
	\~
	*/
	public enum WrapErrorReaction
	{
		/**
		\~korean
		´ëÈ­ »óÀÚ¸¦ º¸¿©ÁØ´Ù. °³¹ß °úÁ¤¿¡¼­´Â ¿ä±äÇÏÁö¸¸ ¿£µåÀ¯Àú ÀÔÀå¿¡¼­´Â Ç®½ºÅ©¸°ÀÎ °æ¿ì ÇÁ¸®Â¡À¸·Î º¸ÀÏ ¼ö ÀÖ¾î¼­ µÇ·¹ ¹®Á¦ Ã£±â°¡ ´õ ¾î·Á¿ï ¼ö ÀÖ´Ù.

		\~english
		Shows chat box. This may be useful during development process but it can also be very troublesome since the chat box can be seen to end users as full screen freezing.

		\~chinese
		?ãÆ???¡£?î¤???ïïñéŞªßÈñìé©£¬Ó£?éÍõÌ?éÄ?î¤îï?ñéÊ¦Òö??Ğì?freezing£¬????Ê¦ÒöÚãì»ÌÚÊ¥Íİ?¡£

		\~japanese
		\~
		*/
		ErrorReaction_MessageBox,
		/**
		\~korean
		Å©·¡½Ã¸¦ À¯¹ßÇÑ´Ù. ¿£µåÀ¯Àú ÀÔÀå¿¡¼­´Â Å©·¡½Ã·Î ³ªÅ¸³ª¹Ç·Î ¸±¸®ÁîµÈ °æ¿ì ¹®Á¦¸¦ ´õ ½±°Ô Ã£À» ¼ö ÀÖ´Ù.
		´Ü, \ref minidump  µîÀ» È¥¿ëÇØ¾ß ±× °¡Ä¡°¡ ÀÖ´Ù.

		\~english
		Causes a crash. From end users' point of view, this is definitely a crash so it can be rather easier to find what the problem is when released.
		But, it is more effective when used along with \ref minidump.

		\~chinese
		??crash¡£î¤õÌ?éÄ??ãÆ?crash£¬Ê¦ÒöÌÚé»æ¶?ÓğreleaseîÜê«ì×¡£
		Ó£é©ûèéÄ\ref minidump%Ôõî¦?êóĞìËÀ?¡£

		\~japanese
		\~
		*/
		ErrorReaction_AccessViolation,
		/**
		\~korean
		µğ¹ö°Å Ãâ·ÂÃ¢¿¡¼­¸¸ º¸¿©Áı´Ï´Ù. Å©·¡½Ã³ª ´ëÈ­»óÀÚ¸¦ ¶ç¿öÁÙ¸¸ÇÑ »óÈ²ÀÌ ¾Æ´Ï¶ó¸é ÀÌ¿É¼ÇÀ» »ç¿ëÇÏ½Ê½Ã¿À.

		\~english
		It shows only debugger output screen. If you can not pop up crash or message box, please use this option.

		\~chinese
		ñş?ãÆî¤???õó?¡£ÜôãÀ?ãÆcrashûäíº???îÜï×?îÜ?£¬?ŞÅéÄó®??¡£

		\~japanese
		\~
		*/
		ErrorReaction_DebugOutput,
		/**
		\~korean
		µğ¹ö°Å ºê·¹ÀÌÅ©¸¦ °Ì´Ï´Ù. ÇØ´ç¿É¼ÇÀº µğ¹ö±× ¸ğµå¿¡¼­¸¸ »ç¿ëÇÏ½Ê½Ã¿À.
		\~english
		\~
		*/
		ErrorReaction_DebugBreak
	};

	/**
	\~korean
	¿¬»ê Á¾·ù

	\~english
	Operation type

	\~chinese
	?ß©??¡£

	\~japanese
	\~
	*/
	public enum WrapValueOperType
	{
		/**
		\~korean
		µ¡¼À

		\~english
		Addition

		\~chinese
		Ê¥Ûö¡£

		\~japanese
		\~
		*/
		ValueOperType_Plus,
		/**
		\~korean
		»¬¼À

		\~english
		Subtraction

		\~chinese
		?Ûö

		\~japanese
		\~
		*/
		ValueOperType_Minus,
		/**
		\~korean
		°ö¼À

		\~english
		Multiplication

		\~chinese
		ã«Ûö¡£

		\~japanese
		\~
		*/
		ValueOperType_Multiply,
		/**
		\~korean
		³ª´°¼À

		\~english
		Division

		\~chinese
		ğ¶Ûö¡£

		\~japanese
		\~
		*/
		ValueOperType_Division
	};

	/**
	\~korean
	ºñ±³ Á¾·ù

	\~english
	Comparison type

	\~chinese
	İï???¡£

	\~japanese
	\~
	*/
	public enum WrapValueCompareType
	{
		/**
		\~korean
		Å©°Å³ª °°À¸¸é

		\~english
		Greater or equal

		\~chinese
		ÓŞûäÔõéÍ¡£

		\~japanese
		\~
		*/
		ValueCompareType_GreaterEqual,

		/**
		\~korean
		Å©¸é

		\~english
		Greater

		\~chinese
		ÓŞîÜ?¡£

		\~japanese
		\~
		*/
		ValueCompareType_Greater,

		/**
		\~korean
		ÀÛ°Å³ª °°À¸¸é

		\~english
		Less or equal

		\~chinese
		á³ûäÔõéÍ¡£

		\~japanese
		\~
		*/
		ValueCompareType_LessEqual,

		/**
		\~korean
		ÀÛÀ¸¸é

		\~english
		Less

		\~chinese
		á³îÜ?¡£

		\~japanese
		\~
		*/
		ValueCompareType_Less,

		/**
		\~korean
		°°À¸¸é

		\~english
		Equal

		\~chinese
		ÔõéÍ¡£

		\~japanese
		\~
		*/
		ValueCompareType_Equal,

		/**
		\~korean
		´Ù¸£¸é

		\~english
		Not equal

		\~chinese
		ÜôÔÒîÜ?¡£

		\~japanese
		\~
		*/
		ValueCompareType_NotEqual
	};

	/**
	\~korean
	¾ÏÈ£È­ ¼öÁØ

	\~english
	Encryption Level

	\~chinese
	Ê¥ÚËâ©øÁ¡£

	\~japanese
	\~
	*/
	public enum WrapEncryptLevel
	{
		/**
		\~korean
		AES ¾ÏÈ£È­ ¼öÁØ ÇÏ

		\~english
		AES encryption level Low

		\~chinese
		AES Ê¥ÚËâ©øÁî¸¡£

		\~japanese
		\~
		*/
		EncryptLevel_Low = 128,
		/**
		\~korean
		AES ¾ÏÈ£È­ ¼öÁØ Áß

		\~english
		AES encryption level Middle

		\~chinese
		AES Ê¥ÚËâ©øÁñé¡£

		\~japanese
		\~
		*/
		EncryptLevel_Middle = 192,
		/**
		\~korean
		AES ¾ÏÈ£È­ ¼öÁØ »ó

		\~english
		AES encryption level High

		\~chinese
		AES Ê¥ÚËâ©øÁß¾¡£

		\~japanese
		\~
		*/
		EncryptLevel_High = 256,
	};

	/**
	\~korean
	Fast ¾ÏÈ£È­ ¼öÁØ

	\~english
	Fast encryption level

	\~chinese
	Fast Ê¥ÚËâ©øÁ¡£

	\~japanese
	\~
	*/
	public enum WrapFastEncryptLevel
	{
		/**
		\~korean
		Fast ¾ÏÈ£È­ ¼öÁØ ÇÏ

		\~english
		Fast encryption level Low

		\~chinese
		FastÊ¥ÚËâ©øÁî¸¡£

		\~japanese
		\~
		*/
		FastEncryptLevel_Low = 512,
		/**
		\~korean
		Fast ¾ÏÈ£È­ ¼öÁØ Áß

		\~english
		Fast encryption level Middle

		\~chinese
		FastÊ¥ÚËâ©øÁñé¡£

		\~japanese
		\~
		*/
		FastEncryptLevel_Middle = 1024,
		/**
		\~korean
		Fast ¾ÏÈ£È­ ¼öÁØ »ó

		\~english
		Fast encryption level High

		\~chinese
		FastÊ¥ÚËâ©øÁß¾¡£

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
	HostID Àç»ç¿ë ±â´É ¿É¼ÇÀÔ´Ï´Ù.

	\~english
	It is an option for HostID reuse function.

	\~chinese
	HostIDãÀî¢ŞÅéÄĞüÒö??¡£

	\~japanese
	HostIDî¢ŞÅéÄÑ¦Òö«ª«×«·«ç«óªÇª¹¡£

	\~
	*/
	public enum WrapHostIDGenerationPolicy
	{
		/**
		\~korean
		HostID Àç»ç¿ë ±â´ÉÀ» »ç¿ëÇÕ´Ï´Ù.
		-±âº»°ªÀÔ´Ï´Ù.

		\~english
		It uses a HostID reuse function.
		-It is a default value.

		\~chinese
		HostID ŞÅéÄî¢ŞÅéÄĞüÒö¡£
		-?ĞñÜâ?¡£.

		\~japanese
		HostIDî¢ŞÅéÄÑ¦ÒöªòŞÅª¤ªŞª¹¡£
		?«Ç«Õ«©«ë«Èö·ªÇª¹

		\~
		*/
		HostIDGenerationPolicy_Recycle = 1,

		/**
		\~korean
		HostID Àç»ç¿ë ±â´ÉÀ» »ç¿ëÇÏÁö ¾Ê½À´Ï´Ù.

		\~english
		It does not use a HostID reuse function.

		\~chinese
		HostID ÜôŞÅéÄî¢ŞÅéÄĞüÒö¡£.

		\~japanese
		HostIDî¢ŞÅéÄÑ¦ÒöªòŞÅª¤ªŞª»ªó¡£

		\~
		*/
		HostIDGenerationPolicy_NoRecycle,
	};

	/**
	\~korean
	½º·¹µå ¸ğµ¨ÀÔ´Ï´Ù.

	\~english
	Thread model.

	\~chinese
	?ïïÙ¼úş¡£

	\~japanese
	«¹«ì«Ã«É«â«Ç«ëªÇª¹¡£

	\~
	*/
	public enum WrapThreadModel
	{
		/**
		\~korean
		´ÜÀÏ ½º·¹µå ¸ğµ¨ÀÔ´Ï´Ù. »ç¿ëÀÚ°¡ ¸¸µç ½º·¹µå À§¿¡¼­ ÀÛµ¿ÇÔÀ» ÀÇ¹ÌÇÕ´Ï´Ù.
		µû·Î ½º·¹µå°¡ ¾øÀ¸¹Ç·Î »ç¿ëÀÚ´Â Proud::CNetClient::FrameMove¸¦ ÃÖ¼Ò ¸Å 1/60ÃÊ¸¶´Ù Áö¼ÓÀûÀ¸·Î È£ÃâÇØ ÁÖ¾î¾ß ÇÕ´Ï´Ù.

		\~english
		Single thread model. Runs code on threads created by user.
		As there is no networker thread, You must call Proud::CNetClient::FrameMove for every 1/60 seconds.

		\~chinese
		??ïïÙ¼úş¡£?ú¼î¤éÄ??ËïîÜ?ïïò®¡£
		ë¦éÍ?êó?Ø¡îÜ?ïï£¬éÄ?âÍé©õÌá´ 1/60 õ©?Ì°ò¥??éÄ Proud::CNetClient::FrameMove¡£

		\~japanese
		«·«ó«°«ë«¹«ì«Ã«É«â«Ç«ëªÇª¹¡£«æ?«¶?ª¬íÂà÷ª·ª¿«¹«ì«Ã«Éß¾ªÇÔÑíÂª¹ªëª³ªÈªòëòÚ«ª·ªŞª¹¡£
		Ü¬ªË«¹«ì«Ã«Éª¬ªÊª¤ª¿ªá¡¢«æ?«¶?ªÏProud :: CNetClient :: FrameMoveªòõÌá³Øİ1/60õ©ª´ªÈªË??îÜªËû¼ªÓõóª¹ù±é©ª¬ª¢ªêªŞª¹¡£

		\~
		*/
		ThreadModel_SingleThreaded = 1,

		/**
		\~korean
		¸ÖÆ¼ ½º·¹µå ¸ğµ¨ÀÔ´Ï´Ù. Thread poolÀ» µû·Î ¸¸µé°í ±× À§¿¡¼­ ÀÛµ¿ÇÔÀ» ÀÇ¹ÌÇÕ´Ï´Ù.

		\~english
		Multi thread model. Runs code on the separated thread pool.

		\~chinese
		Òı?ïïÙ¼úş¡£???Ëï?ïïò®??ú¼î¤ó®ß¾¡£

		\~japanese
		«Ş«ë«Á«¹«ì«Ã«É«â«Ç«ëªÇª¹¡£ Thread poolªòÜ¬?ªËíÂà÷ª·¡¢ª½ªÎß¾ªÇÔÑíÂª¹ªëª³ªÈªòëòÚ«ª·ªŞª¹¡£
		\~
		*/
		ThreadModel_MultiThreaded,

		/**
		\~korean
		¿ÜÀå ½º·¹µå ¸ğµ¨ÀÔ´Ï´Ù. »ç¿ëÀÚ°¡ ¸¸µç Proud.CThreadPool À§¿¡¼­ ÀÛµ¿ÇÔÀ» ÀÇ¹ÌÇÕ´Ï´Ù.

		\~english
		Use-external-thread model. Runs code on Proud.CThreadPool instance create by user.

		\~chinese
		èâİ»?ïïÙ¼úş¡£?ú¼î¤éÄ??ËïîÜ Proud.CThreadPool¡£

		\~japanese
		èâ?«¹«ì«Ã«É«â«Ç«ëªÇª¹¡£«æ?«¶?ª¬íÂà÷ª·ª¿Proud.CThreadPoolß¾ªÇÔÑíÂª¹ªëª³ªÈªòëòÚ«ª·ªŞª¹¡£

		\~
		*/
		ThreadModel_UseExternalThreadPool,
	};


	//À¯ÀÏÇÑ ³»ºÎ¿ë ÄÚµå WrapCVariant ¿¡ ¹«½¼ °ª µé¾î°¡ÀÖ³ª
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