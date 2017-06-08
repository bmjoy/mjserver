#ifndef _OPCODES_H
#define _OPCODES_H

enum eMessageFromSeverToClientType
{
	eTypeNULL =	 0x000	,
	eTypeISMATCH,							//������ʼ
	eTypeISSECONETURN,						//�Ƿ���븴��
	eTypeISPLAYERGETOUT,					//����̭
	eTypeISCHANGETABLE,						//�Ƿ��������
	eTypeNUMPLAYONTABLE,					//�����ϵ�����
	eTypeTHEPLACEONMATCH,					//��õ�����
	eTypeWAITFOROTHERS,						//�ȴ�����������	
	eTypeROOMBASECHANGED,					//���䱶�ʸ���
	eTypeMATCHEXIT,							//�����������ȡ��;
};


enum enumRegisterType
{
	RegisterType_NULL=0,
	RegisterType_PhoneVerify_Register,		// ����ֻ���֤ע����
	RegisterType_PhoneVerify_Find,			// �ֻ��һػ�ȡ��֤��
	RegisterType_NormalRegister,			// ��ͨע��
	RegisterType_FastRegister,				// ����ע��
	RegisterType_PhoneRegister,				// �ֻ���ע��
	RegisterType_DeviceVerify_Find,			// �豸���һ�
	RegisterType_GetPhoneVerify_Find,		// �ֻ��˺��һ�ͨ����֤��
	RegisterType_SendLatitudeAndLongitude,	//��γ��;
	RegisterType_LBSFriendsNear,			//LBS ���Ҹ�������;
};

enum enumHttpRequest
{
	REQUESTTYPE_NULL=0,
	REQUESTTYPE_RELOADUSERINFO,			// ��������userinfo��Ϣ
	REQUESTTYPE_REQUESTGAMEINFO,		// ����gameinfo��Ϣ
};

enum enumAccountMemUpdateType
{
	AMUPDATETYPE_NULL = 0,		
	AMUPDATETYPE_All,
	AMUPDATETYPE_USERINFO,				// ֻ����USERINFO������Ϣ
};

enum enumFriendReqType
{
	REQUESTADD_FRIEND = 0,				//��������
	REQUESTDEL_FRIEND,					//ɾ������	
	REQUESTAGREE_FRIEND,				//ͬ���Ϊ����
	REQUESTREFUSE_FRIEND,				//�ܾ���Ϊ����
	REQUESTFIND_FRIEND,					//���Һ���
};

enum enumMatchRequest
{
	MATCHREQUEST_HISTORYNULL = 0,		
	MATCHREQUEST_HISTORY,
	
};

enum Opcodes
{
	MSG_NULL								= 0x000	,
	
	///ͨ��============================================================================================================================
	MSG_GENERAL_NULL					= 0,
	MSG_SERVERREGISTERED	,			// ����������ע��
	MSG_REGISTERED	,					// ע��
	MSG_DECRYPT	,

	MSG_PING,							// PING
	MSG_PONG,							// PING
	MSG_ERROR,							// ͨ�ô�����Ϣ

	MSG_PROTOTEST,						// GOOGLE PROTOBUF ����Э��

	///HTTP���============================================================================================================================
	MSG_HTTP_NULL						= 100,			// 100-299
	MSG_HTTPTOA_INFO,					// HTTP��������userinfo����					
	MSG_SA_HTTPACCOUNTINFO,				// HTTP���ط����˺�����
	MSG_SC_RESETUSERINFO	,			// �����û���Ϣ
	MSG_WH_GOLDSCHANGED,				// web �������صĸ��Ľ��;
	MSG_WH_LBSRELATEDMESSAGE,			// LBS���Э��;

	///������֮��ͨ��======================================================================================================================
	MSG_SERVER_NULL						= 300,			// 300-499
	MSG_SERVER_STATENOTIFY,				// ���״̬�仯��GF->AM��				CGame_STOA_PlayerStateNotify.h
	MSG_SERVER_ITEMCHANGE,				// ��ҽ�Ǯ���߱仯��GF->AM->DB��		CGame_STOA_ItemChange.h
	MSG_SERVER_MATCHHIS,				// ��ұ�����ʷ�仯��GF->AM->DB��		CGame_STOA_MatchHis.h
	MSG_SERVER_GAMEOVER,				// ��Ϸ��������GF->AM->DB��				CGame_STOA_GameOver.h
	MSG_SERVER_LOGIN,					// ��ҵ���ǳ���������GF->AM��			CAccount_STOA_Login.h
	




	///��½���============================================================================================================================
	MSG_LOGIN_NULL						= 500,
	MSG_CS_LOGIN,						// ��½��� ����
	MSG_CS_LOGINLOGIN	,				
	MSG_SC_LOGININFO	,				// ��½��Ϣ
	MSG_SC_REGISTER	,					// ע��
	MSG_CS_REGISTER	,					// 

	MSG_SA_ACCOUNTFIND,					// ���������˺ŷ������˺�����
	MSG_SA_ACCOUNTREGISTER,				// ���������˺ŷ�����ע���˺�����
	MSG_AS_ACCOUNTINFO,	
	MSG_MEM_GAMEINFO	,				// ���ڴ����ݿⷵ��gameinfo


	///��Ϸ�������=========================================================================================================================
	MSG_ROOM_NULL						= 600,
	MSG_SC_ROOMLIST	,
	MSG_SC_MATCHLIST	,
	MSG_CS_ENTERROOM	,	

	///��Ϸ����ͨ�����=====================================================================================================================
	MSG_CARDGAME_NULL					= 700,
	MSG_WH_CLIENTTRUSTEESHIP, 			// �ͻ��������й�
	MSG_SC_CHANGEGOLD,					

	///��Ϸ�ܵÿ����=====================================================================================================================
	MSG_PDKGAME_NULL					= 800,
	MSG_SC_GAMESTART,					// ��Ϸ��ʼ ����
	MSG_SC_GAMEOVER,					// ��Ϸ����
	MSG_SC_TURNROUND,					// �ֻ�������
	MSG_CS_GAMEOUTCARD,					// ����
	MSG_SC_GAMEOUTCARD,					// ֪ͨ�����˳�����
	MSG_CS_GAMEREADY,					// ׼��
	MSG_SC_GAMENOTCANOUT,				// Ҫ����
	MSG_SC_GAMERECONNECT,				// �����ƾ�


	///��Ϸ����������=====================================================================================================================
	MSG_MATCH_NULL						= 900,
	MSG_CS_Match_Signup,				// ��������
	MSG_CS_Competition,					// �������;
	MSG_CS_CApplyEnterCompetition,		// �ͻ�����������������
	MSG_SC_MATCHMESSAGE,				// ����֪ͨ��Ϣ
	MSG_SC_HISTORY,						// ������ʷ;
	MSG_CS_MATCHREQUEST,				// ��������
	MSG_CS_MATCHRANK,					// ��������
	MSG_SC_MATCHRECONNECT,				// ��������


	//�������
	MSG_FRIEND_NULL						= 1000,
	MSG_CS_FRIENDREQUEST,				//���������˺ŷ�������Ӻ�������
	MSG_SC_FRIENDREQUEST,				//�ڴ���������˺ŷ��������غ�������
	MSG_CS_FRIENDLIST,					//�����б�	
	MSG_SC_FRIENDLIST,					//�����б���
	MSG_CS_FRIENDTALK,					//���ͺ�������
	MSG_SC_FRIENDTALK,					//���պ�������
	MSG_CS_FRIENDRECORD,				//����鿴�����¼
	MSG_SC_FRIENDRECORD,				//���պ��������¼
	MSG_CS_FRIENDRECORDLIST,			//����鿴�����¼�б�
	MSG_SC_FRIENDRECORDLIST,			//���պ��������¼�б�����
	MSG_SC_FRIENDTALKWINDOW,			//���ʹ򿪴���״̬

	MSG_CS_PLAYERINFO,					//�����Ϣ����
	NUM_MSG_TYPES	,	// max msg number
};

#endif	//_OPCODES_H
