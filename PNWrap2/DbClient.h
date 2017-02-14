#pragma once
#include "stdafx.h"
using namespace Proud;

namespace PNWrap2
{
	class Manager;

	class CDbClient
	{
	public:
		CDbClient(Manager *pOwner);
		~CDbClient(void);
		Manager *m_pOwner;

		CAutoPtr<CDbCacheClient2> m_DbClient;

		Proud::String m_serverAddr;

		INT_PTR	m_diffCustomArg;

	public:
		CLoadedData2Ptr m_data;

		Proud::Guid		m_SessionGuid;	// RootSessionGuid
		Proud::Guid		m_heroGuid;
		Proud::Guid		m_itemGuid;
		Proud::Guid		m_friendGuid;

		Proud::String	m_GamerName;
		Proud::String	m_heroName;

	private:
		CriticalSection m_CSLock;
	public:
		// Request�� �޽������� ack �� �Դ����� üũ �մϴ�.
		// Blocked�� �Ϲ��� �Լ���ܿ��� �ݵ�� ack�� �� �Ŀ� ó�� �Ǿ�߸� �մϴ�.

		// It has to check receiving ack at Request type message.
		// It has to process after receiving ack except Blocked and one-sided type functions.
		bool bRequestComplete;
		void RequestCompleteTrue();
		bool GetRequestComplete();

	public:

		void SimpleTest();


		bool AddGamerData();
		bool AddHeroData();
		bool UpdateHeroData();
		bool RemoveHeroData();
		bool BlockedAddItem();
		bool BlockedUpdateItem();
		bool BlockedRemoveItem();
		bool AddFriend();
		bool UpdateFriend();
		bool RemoveFriend();
		bool RemoveGamerData();

		// NonCacheTest
	public:
		CPropNodePtr addData;

		void LoadRootAddExclusive();
		void LoadDataSnapshot();
		void AddNonExclusive();
		void AddChildNonExclusive();
		void RemoveNonExclusive(Proud::Guid &removeUUID);
		void RequestModify(Proud::ValueOperType type, int value);
		void RequestSetIfValue(Proud::ValueCompareType tyep, int value, int value2);
	};
}