#ifndef _CErrorCode_H
#define _CErrorCode_H


//���ط��ش�������

enum enumHttpErrorCode
{
	ErrorCode_NULL=0,
	ErrorCode_UserAccountRegisterFail,			// �˺�ע��ʧ��
	ErrorCode_PhoneRegisterFail,			// �ֻ�ע��ʧ��
	ErrorCode_FastRegisterFail,					//����ע��ʧ��
	ErrorCode_PhoneVerify_FindFail,				// �ֻ��˺��һ�ʧ��
	ErrorCode_DeviceVerify_FindFail,		//�豸���һ�ʧ��
	ErrorCode_DeviceVerifyRequestFail,		//��֤������ʧ��
	ErrorCode_LBSFindsFriendsNearbyFail,		//LBS���Ҹ�������ʧ��
};


enum enumErrorCode
{
	ErrorCode_AccountVerifyFail,			// �˺���֤ʧ��
	ErrorCode_AccountVerifySuccess,			// �˺���֤�ɹ�

	ErrorCode_AccountRegisterFail,			// ע�᷵�ش�����ʱ�Ǵ������Դ�������أ�;

	ErrorCode_AccountOtherGameLogin,		// ���˺��Ѿ���������Ϸ��½
	ErrorCode_AccountRepeatLogin,			// �ظ���¼
	ErrorCode_AccountUnLoginSuc,			// �˳���½�ɹ�
	ErrorCode_UnLogin_InRoom,				// �ڷ�����  �������˳���Ϸ


	ErrorCode_EnterRoomSuccess,				// ���뷿��ɹ�
	ErrorCode_ExitRoomSuccess,				// �˳�����ɹ�
	ErrorCode_EnterRoomFailed,				// ���뷿��ʧ��
	ErrorCode_NoReadyExitRoom,				// ��ʱ�䲻׼���˳�����

	ErrorCode_Http_NoAccoutID,				// û������˺�  �˺�ID����

	ErrorCode_Http_ChangeGoldSuc,			// �Ӽ���ҳɹ�


	ErrorCode_Match_Begin,
	ErrorCode_Match_NotAtSignup,			// ���ڱ����׶�
	ErrorCode_Match_HaveRoomID,				// ���������з���ID
	ErrorCode_Match_LvLimit,				// �ȼ�����
	ErrorCode_Match_VipLvLimit,				// Vip�ȼ�����
	ErrorCode_Match_NoMoney,				// �������Ѳ���
	ErrorCode_Match_SignupSuc,				// �����ɹ�
	ErrorCode_Match_UnSignupSuc,			// �����ɹ�
	ErrorCode_Match_ReSignupSuc,			// �ظ�����
	ErrorCode_Match_MaxPlayer,				// ������������
	
	ErrorCode_Match_End,

	ErrorCode_FriendAdd_Fail,				//��������ʧ��
	ErrorCode_FriendDel_Fail,				//ɾ������ʧ��
	ErrorCode_FriendAgree_Fail,				//ͬ����Ӻ���ʧ��
	ErrorCode_FriendRefuse_Fail,			//�ܾ���Ӻ���ʧ��
	ErrorCode_FriendFind_NoFriend,			//���Ѳ�����
	ErrorCode_FriendFind_Fail,				//���Һ���ʧ��
	ErrorCode_FriendList_Fail,				//���Һ����б�ʧ��
	ErrorCode_FriendTalk_Fail,				//���ͺ�����Ϣʧ��
	ErrorCode_FriendRecord_Fail,			//��ȡ�����¼ʧ��
	ErrorCode_FriendRecordList_Fail,		//��ȡ�����¼�б�ʧ��
	ErrorCode_FriendAdd_Repeat,				//�ظ���Ӻ�������


	ErrorCode_Game_NoMoney,					// Ǯ������
	ErrorCode_Game_NoMoneyToEnterRoom,		// Ǯ�������뷿��

	ErrorCode_Game_PlayerWarning,			//��ұ���
};


enum enumBackCodeErrorType					//php ���󷵻� ���������ͺ� ����
{
	
	enumBackCodeErrorNull =0,
	//�˺�ע��ӿ�
	enumBackCodeError_RegisterLackParameter =1,				//ȱʧ����
	enumBackCodeError_RegisterParameterError,				//��������
	enumBackCodeError_RegisterValidationFail,				//��֤����
	enumBackCodeError_RegisterAccountThere,					//�˺Ŵ���
	enumBackCodeError_RegisterDataUpdataError,				//���ݸ���ʧ��



	//����ע��ӿ�
	enumBackCodeError_FastRegisterLackParameter =10,				//ȱʧ����
	enumBackCodeError_FastRegisterParameterError,					//��������
	enumBackCodeError_FastRegisterValidationFail,					//��֤����
	enumBackCodeError_FastRegisterGetAorPError,						//��ȡ�˺�����ʧ��

	//�ֻ���֤������ӿ�

	enumBackCodeError_ValidationLackParameter =20,				//ȱʧ����
	enumBackCodeError_ValidationParameterError,					//��������
	enumBackCodeError_ValidationFail,							//��֤����
	enumBackCodeError_ProduceValidationError,				//������֤��ʧ��

	//�ֻ�ע��
	enumBackCodeError_PhoneRegisterLackParameter =30,				//ȱʧ����
	enumBackCodeError_PhoneRegisterParameterError,					//��������
	enumBackCodeError_PhoneRegisterValidationFail,					//��֤����
	enumBackCodeError_PhoneRegisterAccountThere,					//�˺Ŵ���
	enumBackCodeError_PhoneRegisterDataUpdataError,					//���ݸ���ʧ��
	enumBackCodeError_PhoneRegisterLackParameterPthoneorVal,		//�绰������֤��ȱʧ;
	enumBackCodeError_PhoneRegisterValidationFailure ,				//��֤��ʧЧ
	enumBackCodeError_PhoneRegisterDataExtractError,				//������ȡʧ��





};


#endif	//_CErrorCode_H