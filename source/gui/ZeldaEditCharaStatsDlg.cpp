// ZeldaEditCharaStatsDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ZeldaHWLSaveEditorGUI.h"
#include "afxdialogex.h"
#include "ZeldaEditCharaStatsDlg.h"


// CZeldaEditCharaStatsDlg-Dialogfeld

IMPLEMENT_DYNAMIC(CZeldaEditCharaStatsDlg, CDialogEx)

CZeldaEditCharaStatsDlg::CZeldaEditCharaStatsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CZeldaEditCharaStatsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

CZeldaEditCharaStatsDlg::~CZeldaEditCharaStatsDlg()
{
}

void CZeldaEditCharaStatsDlg::DoDataExchange(CDataExchange* pDX)
{
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	//menu
	CMenu *cm_menu = GetMenu();
	CMenu* cm_submenu = cm_menu->GetSubMenu(1);
	cm_submenu->CheckMenuItem(1, MF_CHECKED | MF_BYPOSITION);

	cm_submenu = cm_submenu->GetSubMenu(1);
	cm_submenu->CheckMenuItem(0, MF_CHECKED | MF_BYPOSITION);

	//own inits
	save = CZeldaHWLSaveEditorGUIApp::save;

	if (save != nullptr)
	{
		for (int i = IDC_EDIT_CHARA_LVL1; i <= IDC_EDIT_CHARA_LVL24; i++)
		{
			GetDlgItem(i)->EnableWindow(true);
		}

		for (int i = IDC_EDIT_CHARA_EXP1; i <= IDC_EDIT_CHARA_EXP24; i++)
		{
			GetDlgItem(i)->EnableWindow(true);
		}

		for (int i = IDC_EDIT_CHARA_ATK1; i <= IDC_EDIT_CHARA_ATK24; i++)
		{
			GetDlgItem(i)->EnableWindow(true);
		}

		for (int i = IDC_CHECK_CHARA_UNLOCK1; i <= IDC_CHECK_CHARA_UNLOCK24; i++)
		{
			GetDlgItem(i)->EnableWindow(true);
		}

		this->calc_players();

	}
	else
	{

		for (int i = IDC_STATIC_CHARA1; i <= IDC_STATIC_CHARA24; i++)
		{
			SetDlgItemText(i, L"Chara");
		}

		for (int i = IDC_EDIT_CHARA_LVL1; i <= IDC_EDIT_CHARA_LVL24; i++)
		{
			SetDlgItemText(i, L"");
			GetDlgItem(i)->EnableWindow(false);
		}

		for (int i = IDC_EDIT_CHARA_EXP1; i <= IDC_EDIT_CHARA_EXP24; i++)
		{
			SetDlgItemText(i, L"");
			GetDlgItem(i)->EnableWindow(false);
		}	

		for (int i = IDC_EDIT_CHARA_ATK1; i <= IDC_EDIT_CHARA_ATK24; i++)
		{
			SetDlgItemText(i, L"");
			GetDlgItem(i)->EnableWindow(false);
		}

		for (int i = IDC_CHECK_CHARA_UNLOCK1; i <= IDC_CHECK_CHARA_UNLOCK24; i++)
		{
			((CButton*)GetDlgItem(i))->SetCheck(0);
			GetDlgItem(i)->EnableWindow(false);
		}

	}

	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CZeldaEditCharaStatsDlg, CDialogEx)
	ON_BN_CLICKED(ID_EXIT, &CZeldaEditCharaStatsDlg::OnBnClickedExit)
	ON_BN_CLICKED(ID_SAVE, &CZeldaEditCharaStatsDlg::OnBnClickedSave)
	ON_CONTROL_RANGE(EN_CHANGE, IDC_EDIT_CHARA_LVL1, IDC_EDIT_CHARA_LVL24, &OnEnChangeLVLEdit)
	ON_CONTROL_RANGE(EN_CHANGE, IDC_EDIT_CHARA_EXP1, IDC_EDIT_CHARA_EXP24, &OnEnChangeEXPEdit)
	ON_CONTROL_RANGE(EN_CHANGE, IDC_EDIT_CHARA_ATK1, IDC_EDIT_CHARA_ATK24, &OnEnChangeATKEdit)
	ON_COMMAND(ID_MENU_ABOUT, &CZeldaEditCharaStatsDlg::OnMenuAbout)
	ON_COMMAND(ID_MENU_EDIT_GENERAL, &CZeldaEditCharaStatsDlg::OnMenuEditGeneral)
	ON_COMMAND(ID_MENU_EDIT_CHARACTERS_STATS, &CZeldaEditCharaStatsDlg::OnMenuEditCharactersStats)
	ON_COMMAND(ID_MENU_EDIT_MATERIALS_BRONZE, &CZeldaEditCharaStatsDlg::OnMenuEditMaterialsBronze)
	ON_COMMAND(ID_MENU_EDIT_MATERIALS_SILVER, &CZeldaEditCharaStatsDlg::OnMenuEditMaterialsSilver)
	ON_COMMAND(ID_MENU_EDIT_MATERIALS_GOLD, &CZeldaEditCharaStatsDlg::OnMenuEditMaterialsGold)
	ON_COMMAND(ID_MENU_MAIN_EXIT, &CZeldaEditCharaStatsDlg::OnMenuMainExit)
END_MESSAGE_MAP()


// CZeldaEditCharaStatsDlg-Meldungshandler
void CZeldaEditCharaStatsDlg::OnBnClickedExit()
{
	// TODO: F�gen Sie hier Ihren Kontrollbehandlungscode f�r die Benachrichtigung ein.
	CZeldaEditCharaStatsDlg::OnOK();
}


void CZeldaEditCharaStatsDlg::OnBnClickedSave()
{
	// TODO: F�gen Sie hier Ihren Kontrollbehandlungscode f�r die Benachrichtigung ein.
	if (save != nullptr)
	{
		try
		{
			this->save_players();
			save->save_file();
		}
		catch (std::exception &e)
		{
			CString str(e.what());
			MessageBox(str, L"Error");
		}
	}
	else{
		CString str("There is no SaveFile opened!");
		MessageBox(str, L"Error");
	}

}

void CZeldaEditCharaStatsDlg::calc_players()
{
	int unused_charas = 0;


	for (int i = 0; i < save->vs_players.size(); i++)
	{
		CString s_player_name(save->get_player(i)->get_name().c_str());

		CString s_player_lvl;
		s_player_lvl.Format(L"%d", save->get_player(i)->get_lvl());

		CString s_player_exp;
		s_player_exp.Format(L"%d", save->get_player(i)->get_exp());

		CString s_player_atk;
		s_player_atk.Format(L"%d", save->get_player(i)->get_atk());

		bool b_player_is_unlock = save->get_player(i)->get_isUnlock();
		CButton *cb_check;


		if (s_player_name == L"???")
		{
			unused_charas++;
			continue;
		}

		SetDlgItemText((IDC_STATIC_CHARA1 + i - unused_charas), s_player_name + L": ");
		SetDlgItemText((IDC_EDIT_CHARA_LVL1 + i - unused_charas), s_player_lvl);
		SetDlgItemText((IDC_EDIT_CHARA_EXP1 + i - unused_charas), s_player_exp);
		SetDlgItemText((IDC_EDIT_CHARA_ATK1 + i - unused_charas), s_player_atk);
		cb_check = (CButton*)GetDlgItem((IDC_CHECK_CHARA_UNLOCK1 + i - unused_charas));
		cb_check->SetCheck(b_player_is_unlock);

		CEdit *e_test = (CEdit*)GetDlgItem((IDC_EDIT_CHARA_LVL1 + i - unused_charas));
		e_test->SetLimitText(3);

		e_test = (CEdit*)GetDlgItem((IDC_EDIT_CHARA_EXP1 + i - unused_charas));
		e_test->SetLimitText(8);

		e_test = (CEdit*)GetDlgItem((IDC_EDIT_CHARA_ATK1 + i - unused_charas));
		e_test->SetLimitText(4);
	}

}

void CZeldaEditCharaStatsDlg::OnEnChangeLVLEdit(UINT nID)
{

	if (SendDlgItemMessage(nID, EM_GETMODIFY, 0, 0))
	{
		if (save != nullptr)
		{
			CString test;
			CEdit *e_test = (CEdit*)GetDlgItem(nID);
			e_test->SetLimitText(3);
			GetDlgItemText(nID, test);
			int i_test = _wtoi(test);

			if (i_test > HWLSaveEdit::HWLPlayer::playerLVLMax)
			{
				test.Format(L"%d", HWLSaveEdit::HWLPlayer::playerLVLMax);
				SetDlgItemText(nID, test);
				e_test->SetLimitText(2);
			}

		}
	}

}

void CZeldaEditCharaStatsDlg::OnEnChangeEXPEdit(UINT nID)
{

	if (SendDlgItemMessage(nID, EM_GETMODIFY, 0, 0))
	{
		if (save != nullptr)
		{
			CString test;
			CEdit *e_test = (CEdit*)GetDlgItem(nID);
			e_test->SetLimitText(8);
			GetDlgItemText(nID, test);
			int i_test = _wtoi(test);

			if (i_test > HWLSaveEdit::HWLPlayer::playerEXPMax)
			{
				test.Format(L"%d", HWLSaveEdit::HWLPlayer::playerEXPMax);
				SetDlgItemText(nID, test);
				e_test->SetLimitText(7);
			}

		}
	}

}

void CZeldaEditCharaStatsDlg::OnEnChangeATKEdit(UINT nID)
{

	if (SendDlgItemMessage(nID, EM_GETMODIFY, 0, 0))
	{
		if (save != nullptr)
		{
			CString test;
			CEdit *e_test = (CEdit*)GetDlgItem(nID);
			e_test->SetLimitText(4);
			GetDlgItemText(nID, test);
			int i_test = _wtoi(test);

			if (i_test > HWLSaveEdit::HWLPlayer::playerATKMax)
			{
				test.Format(L"%d", HWLSaveEdit::HWLPlayer::playerATKMax);
				SetDlgItemText(nID, test);
				e_test->SetLimitText(3);
			}

		}
	}

}

void CZeldaEditCharaStatsDlg::save_players()
{
	if (save != nullptr)
	{
		int unused_charas = 0;

		for (int i = 0; i < save->vs_players.size(); i++)
		{
			CString s_player_name(save->get_player(i)->get_name().c_str());
			CString s_player_lvl;
			CString s_player_exp;
			CString s_player_atk;
			CButton *cb_check;

			if (s_player_name == L"???")
			{
				unused_charas++;
				continue;
			}

			GetDlgItemText((IDC_EDIT_CHARA_LVL1 + i - unused_charas), s_player_lvl);
			int i_player_lvl = _wtof(s_player_lvl);

			GetDlgItemText((IDC_EDIT_CHARA_EXP1 + i - unused_charas), s_player_exp);
			int i_player_exp = _wtof(s_player_exp);

			GetDlgItemText((IDC_EDIT_CHARA_ATK1 + i - unused_charas), s_player_atk);
			int i_player_atk = _wtof(s_player_atk);

			cb_check = (CButton*)GetDlgItem((IDC_CHECK_CHARA_UNLOCK1 + i - unused_charas));
			bool b_player_is_unlock = cb_check->GetCheck();

			save->get_player(i)->set_lvl(i_player_lvl);
			save->get_player(i)->set_exp(i_player_exp);
			save->get_player(i)->set_atk(i_player_atk);
			save->get_player(i)->set_isUnlock(b_player_is_unlock);
			save->get_player(i)->save_Player();
		}

	}

}


void CZeldaEditCharaStatsDlg::OnMenuAbout()
{
	// TODO: F�gen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaAboutDlg about;
	about.DoModal();
}


void CZeldaEditCharaStatsDlg::OnMenuEditGeneral()
{
	// TODO: F�gen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditGeneralDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditCharaStatsDlg::OnMenuEditCharactersStats()
{
	// TODO: F�gen Sie hier Ihren Befehlsbehandlungscode ein.
}


void CZeldaEditCharaStatsDlg::OnMenuEditMaterialsBronze()
{
	// TODO: F�gen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditMaterials dlg(NULL, 0);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaStatsDlg::OnMenuEditMaterialsSilver()
{
	// TODO: F�gen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditMaterials dlg(NULL, 1);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaStatsDlg::OnMenuEditMaterialsGold()
{
	// TODO: F�gen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditMaterials dlg(NULL, 2);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaStatsDlg::OnMenuMainExit()
{
	// TODO: F�gen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditCharaStatsDlg::OnOK();

}
