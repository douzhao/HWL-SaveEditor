// ZeldaEditFairyDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ZeldaHWLSaveEditorGUI.h"
#include "ZeldaEditFairyDlg.h"
#include "afxdialogex.h"


// CZeldaEditFairyDlg-Dialogfeld

IMPLEMENT_DYNAMIC(CZeldaEditFairyDlg, CDialogEx)

CZeldaEditFairyDlg::CZeldaEditFairyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CZeldaEditFairyDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	this->i_fairy = 1;
}

CZeldaEditFairyDlg::~CZeldaEditFairyDlg()
{
}

BOOL CZeldaEditFairyDlg::OnInitDialog()
{
	//calculate the disabled-Items and remove the Menu-Entry, if neccessary
	CZeldaHWLSaveEditorGUIApp::calc_disabled_MenuItems(GetMenu()->GetSubMenu(1));
	return CDialogEx::OnInitDialog();
}

void CZeldaEditFairyDlg::DoDataExchange(CDataExchange* pDX)
{
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//menu
	CMenu *cm_menu = GetMenu();
	CMenu* cm_submenu = cm_menu->GetSubMenu(1);
	cm_submenu->CheckMenuItem(5, MF_CHECKED | MF_BYPOSITION);

	//get the save-content
	save = CZeldaHWLSaveEditorGUIApp::save;

	if (save != nullptr)
	{
		this->i_fairy_max = HWLSaveEdit::HWLGeneral::fairiesMax;

		if (this->i_fairy <= 1)
			GetDlgItem(IDC_FAIRY_PAGE_PREVIOUS)->EnableWindow(false);
		else
			GetDlgItem(IDC_FAIRY_PAGE_PREVIOUS)->EnableWindow(true);

		if (this->i_fairy >= this->i_fairy_max)
			GetDlgItem(IDC_FAIRY_PAGE_NEXT)->EnableWindow(false);
		else
			GetDlgItem(IDC_FAIRY_PAGE_NEXT)->EnableWindow(true);


		for (int i = IDC_EDIT_FAIRY_LVL; i <= IDC_CHECK_FAIRY_UNLOCK; i++)
		{
			GetDlgItem(i)->EnableWindow(true);
			GetDlgItem(i)->ShowWindow(SW_SHOWNORMAL);
		}

		((CEdit*)GetDlgItem(IDC_FAIRY_FAIRYNAME))->SetLimitText(HWLSaveEdit::HWLFairy::fairyNameLength);
		GetDlgItem(IDC_FAIRY_FAIRYNAME)->EnableWindow(true);
		GetDlgItem(IDC_FAIRY_MAX_STATS)->EnableWindow(true);


		CString s_fairy_count;
		s_fairy_count.Format(L"%d / %d", this->i_fairy, this->i_fairy_max);
		SetDlgItemText(IDC_STATIC_FAIRY_COUNT, s_fairy_count);

		this->calc_fairy();
	}else
	{
		SetDlgItemText(IDC_FAIRY_FAIRYNAME, L"");

		for (int i = IDC_EDIT_FAIRY_LVL; i <= IDC_CHECK_FAIRY_UNLOCK; i++)
		{
			SetDlgItemText(i, L"");
			GetDlgItem(i)->ShowWindow(SW_SHOWNORMAL);
			GetDlgItem(i)->EnableWindow(false);
		}

		GetDlgItem(IDC_FAIRY_FAIRYNAME)->EnableWindow(false);
		GetDlgItem(IDC_FAIRY_MAX_STATS)->EnableWindow(false);

		SetDlgItemText(IDC_STATIC_FAIRY_COUNT, L"0 / 0");
		GetDlgItem(IDC_FAIRY_PAGE_PREVIOUS)->EnableWindow(false);
		GetDlgItem(IDC_FAIRY_PAGE_NEXT)->EnableWindow(false);
	}

	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CZeldaEditFairyDlg, CDialogEx)
	ON_COMMAND(ID_MENU_EDIT_FAIRIES, &CZeldaEditFairyDlg::OnMenuEditFairies)
	ON_COMMAND(ID_MENU_EDIT_GENERAL, &CZeldaEditFairyDlg::OnMenuEditGeneral)
	ON_COMMAND(ID_MENU_EDIT_CHARACTERS_STATS, &CZeldaEditFairyDlg::OnMenuEditCharactersStats)
	ON_COMMAND(ID_MENU_EDIT_MATERIALS_BRONZE, &CZeldaEditFairyDlg::OnMenuEditMaterialsBronze)
	ON_COMMAND(ID_MENU_EDIT_MATERIALS_SILVER, &CZeldaEditFairyDlg::OnMenuEditMaterialsSilver)
	ON_COMMAND(ID_MENU_EDIT_MATERIALS_GOLD, &CZeldaEditFairyDlg::OnMenuEditMaterialsGold)
	ON_COMMAND(ID_MENU_EDIT_FAIRYFOODS, &CZeldaEditFairyDlg::OnMenuEditFairyfoods)
	ON_COMMAND(ID_MENU_EDIT_AM_AVMAP, &CZeldaEditFairyDlg::OnMenuEditAmAvmap)
	ON_COMMAND(ID_MENU_EDIT_AM_GSMAP, &CZeldaEditFairyDlg::OnMenuEditAmGsmap)
	ON_COMMAND(ID_MENU_EDIT_AM_MQMAP, &CZeldaEditFairyDlg::OnMenuEditAmMqmap)
	ON_COMMAND(ID_MENU_EDIT_AM_TLMAP, &CZeldaEditFairyDlg::OnMenuEditAmTlmap)
	ON_COMMAND(ID_MENU_EDIT_AM_TMMAP, &CZeldaEditFairyDlg::OnMenuEditAmTmmap)
	ON_BN_CLICKED(ID_SAVE, &CZeldaEditFairyDlg::OnBnClickedSave)
	ON_BN_CLICKED(ID_EXIT, &CZeldaEditFairyDlg::OnBnClickedExit)
	ON_BN_CLICKED(IDC_FAIRY_PAGE_PREVIOUS, &CZeldaEditFairyDlg::OnBnClickedFairyPagePrevious)
	ON_BN_CLICKED(IDC_FAIRY_PAGE_NEXT, &CZeldaEditFairyDlg::OnBnClickedFairyPageNext)
	ON_BN_CLICKED(IDC_FAIRY_MAX_STATS, &CZeldaEditFairyDlg::OnBnClickedFairyMaxStats)
	ON_EN_CHANGE(IDC_EDIT_FAIRY_LVL, &CZeldaEditFairyDlg::OnEnChangeEditFairyLvl)
	ON_EN_CHANGE(IDC_EDIT_FAIRY_TRUST, &CZeldaEditFairyDlg::OnEnChangeEditFairyTrust)
	ON_EN_CHANGE(IDC_EDIT_FAIRY_ITERATOR, &CZeldaEditFairyDlg::OnEnChangeEditFairyIterator)
	ON_COMMAND(ID_MENU_EDIT_CHARACTERS_WEAPONS, &CZeldaEditFairyDlg::OnMenuEditCharactersWeapons)
	ON_COMMAND(ID_MENU_EDIT_AM_MWWMAP, &CZeldaEditFairyDlg::OnMenuEditAmMwwmap)
	ON_COMMAND(ID_MENU_EDIT_AM_KIMAP, &CZeldaEditFairyDlg::OnMenuEditAmKimap)
	ON_COMMAND(ID_MENU_EDIT_AM_GTMAP, &CZeldaEditFairyDlg::OnMenuEditAmGtmap)
	ON_BN_CLICKED(IDC_FAIRY_MAX_STATS_ALL, &CZeldaEditFairyDlg::OnBnClickedFairyMaxStatsAll)
	ON_BN_CLICKED(IDC_FAIRY_UNLOCK_ALL, &CZeldaEditFairyDlg::OnBnClickedFairyUnlockAll)
	ON_COMMAND(ID_MENU_MAIN_EXIT, &CZeldaEditFairyDlg::OnMenuMainExit)
	ON_COMMAND(ID_MENU_EDIT_CHARACTERS_OVERVIEW, &CZeldaEditFairyDlg::OnMenuEditCharactersOverview)
	ON_COMMAND(ID_MENU_EDIT_AM_LRMAP, &CZeldaEditFairyDlg::OnMenuEditAmLrmap)
END_MESSAGE_MAP()


// CZeldaEditFairyDlg-Meldungshandler


void CZeldaEditFairyDlg::OnMenuEditFairies()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
}


void CZeldaEditFairyDlg::OnMenuEditGeneral()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditGeneralDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditFairyDlg::OnMenuEditCharactersStats()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditCharaStatsDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditFairyDlg::OnMenuEditMaterialsBronze()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditMaterials dlg(NULL, 0);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditFairyDlg::OnMenuEditMaterialsSilver()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditMaterials dlg(NULL, 1);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditFairyDlg::OnMenuEditMaterialsGold()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditMaterials dlg(NULL, 2);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditFairyDlg::OnMenuEditFairyfoods()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditFairyFoods dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditFairyDlg::OnMenuEditAmAvmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeMaps dlg(NULL, 0);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditFairyDlg::OnMenuEditAmGsmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeMaps dlg(NULL, 1);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditFairyDlg::OnMenuEditAmMqmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeMaps dlg(NULL, 2);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditFairyDlg::OnMenuEditAmTlmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeMaps dlg(NULL, 3);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditFairyDlg::OnMenuEditAmTmmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeMaps dlg(NULL, 4);
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditFairyDlg::OnMenuEditAmMwwmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeMaps dlg(NULL, 5);
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditFairyDlg::OnMenuEditAmKimap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	int i_map_id = 6;
	int i_skipped_maps = 0;

	for (int i = i_map_id - 1; i < i_map_id; i++)
	{
		if (save->get_amMap(i)->get_isDisabled())
			i_skipped_maps++;
	}

	CZeldaEditAdventureModeMaps dlg(NULL, i_map_id, i_skipped_maps);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditFairyDlg::OnMenuEditAmGtmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	int i_map_id = 7;
	int i_skipped_maps = 0;

	for (int i = i_map_id - 2; i < i_map_id; i++)
	{
		if (save->get_amMap(i)->get_isDisabled())
			i_skipped_maps++;
	}

	CZeldaEditAdventureModeMaps dlg(NULL, i_map_id, i_skipped_maps);
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditFairyDlg::OnMenuEditAmLrmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	int i_map_id = 8;
	int i_skipped_maps = 0;

	for (int i = i_map_id - 3; i < i_map_id; i++)
	{
		if (save->get_amMap(i)->get_isDisabled())
			i_skipped_maps++;
	}

	CZeldaEditAdventureModeMaps dlg(NULL, i_map_id, i_skipped_maps);
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditFairyDlg::OnBnClickedSave()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (save != nullptr)
	{
		try
		{
			this->save_fairy();
			save->save_file();

			CString str("Finish! Saving the current values was successfully.");
			MessageBox(str, L"Information", MB_OK | MB_ICONINFORMATION);
		}
		catch (std::exception &e)
		{
			CString str(e.what());
			MessageBox(str, L"Error", MB_ICONERROR);
		}
	}
	else{
		CString str("There is no SaveFile opened!");
		MessageBox(str, L"Error", MB_ICONERROR);
	}
}


void CZeldaEditFairyDlg::OnBnClickedExit()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	CZeldaEditFairyDlg::OnOK();
}


void CZeldaEditFairyDlg::OnBnClickedFairyPagePrevious()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	this->save_fairy();
	this->i_fairy--;
	this->UpdateData();
}


void CZeldaEditFairyDlg::OnBnClickedFairyPageNext()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	this->save_fairy();
	this->i_fairy++;
	this->UpdateData();
}


void CZeldaEditFairyDlg::OnBnClickedFairyMaxStats()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (save != nullptr)
	{
		save->get_fairy(this->i_fairy - 1)->set_lvl(HWLSaveEdit::HWLFairy::fairyLVLMax);
		save->get_fairy(this->i_fairy - 1)->set_trust(HWLSaveEdit::HWLFairy::fairyTrustMax);
		save->get_fairy(this->i_fairy - 1)->set_iterator(HWLSaveEdit::HWLFairy::fairyIteratorMax);
		save->get_fairy(this->i_fairy - 1)->save_Fairy();

		this->UpdateData();

		CString str("Finish! All needed Values are updated.");
		MessageBox(str, L"Information", MB_OK | MB_ICONINFORMATION);
	}

}

void CZeldaEditFairyDlg::OnBnClickedFairyMaxStatsAll()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (save != nullptr)
	{
		for (int i = 0; i < HWLSaveEdit::HWLGeneral::fairiesMax; i++)
		{
			save->get_fairy(i)->set_lvl(HWLSaveEdit::HWLFairy::fairyLVLMax);
			save->get_fairy(i)->set_trust(HWLSaveEdit::HWLFairy::fairyTrustMax);
			save->get_fairy(i)->set_iterator(HWLSaveEdit::HWLFairy::fairyIteratorMax);
			save->get_fairy(i)->save_Fairy();
		}

		this->UpdateData();

		CString str("Finish! All needed Values are updated.");
		MessageBox(str, L"Information", MB_OK | MB_ICONINFORMATION);
	}

}


void CZeldaEditFairyDlg::OnBnClickedFairyUnlockAll()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (save != nullptr)
	{
		for (int i = 0; i < HWLSaveEdit::HWLGeneral::fairiesMax; i++)
		{
			save->get_fairy(i)->set_isUnlock(true);
			save->get_fairy(i)->save_Fairy();
		}

		this->UpdateData();

		CString str("Finish! All needed Fairies are unlocked.");
		MessageBox(str, L"Information", MB_OK | MB_ICONINFORMATION);
	}
}


void CZeldaEditFairyDlg::calc_fairy()
{
	CString s_name, s_lvl, s_trust, s_iterator;

	s_name = (save->get_fairy(this->i_fairy - 1)->get_name()).c_str();
	SetDlgItemText(IDC_FAIRY_FAIRYNAME, s_name);

	s_lvl.Format(L"%d", save->get_fairy(this->i_fairy - 1)->get_lvl());
	SetDlgItemText(IDC_EDIT_FAIRY_LVL, s_lvl);

	s_trust.Format(L"%d", save->get_fairy(this->i_fairy - 1)->get_trust());
	SetDlgItemText(IDC_EDIT_FAIRY_TRUST, s_trust);

	s_iterator.Format(L"%d", save->get_fairy(this->i_fairy - 1)->get_iterator());
	SetDlgItemText(IDC_EDIT_FAIRY_ITERATOR, s_iterator);

	CButton *cb_check;
	cb_check = (CButton*)GetDlgItem(IDC_CHECK_FAIRY_UNLOCK);
	cb_check->SetCheck(save->get_fairy(this->i_fairy - 1)->get_isUnlock());
}

void CZeldaEditFairyDlg::save_fairy()
{
	
	int *i_values = new int[(IDC_CHECK_FAIRY_UNLOCK - IDC_EDIT_FAIRY_LVL)+1];
	int i_counter = 0;
	
	for (int i = IDC_EDIT_FAIRY_LVL; i <= IDC_CHECK_FAIRY_UNLOCK; i++)
	{
		CString cs_tmp_value;
		GetDlgItemText(i, cs_tmp_value);
		i_values[i_counter] = _wtof(cs_tmp_value);
		i_counter++;
	}

	CString cs_name;
	GetDlgItemText(IDC_FAIRY_FAIRYNAME, cs_name);

	std::string s_name = save->WideStringAsCharToByteString(cs_name);
	save->get_fairy(this->i_fairy - 1)->set_name(s_name);

	CButton *cb_check;
	cb_check = (CButton*)GetDlgItem(IDC_CHECK_FAIRY_UNLOCK);
	i_values[3] = cb_check->GetCheck();

	save->get_fairy(this->i_fairy - 1)->set_lvl(i_values[0]);
	save->get_fairy(this->i_fairy - 1)->set_trust(i_values[1]);
	save->get_fairy(this->i_fairy - 1)->set_iterator(i_values[2]);
	save->get_fairy(this->i_fairy - 1)->set_isUnlock(i_values[3]);

	delete i_values;
	save->get_fairy(this->i_fairy - 1)->save_Fairy();
	
}

void CZeldaEditFairyDlg::OnEnChangeEditFairyLvl()
{
	if (save != nullptr)
	{
		CString test;
		CEdit *e_test = (CEdit*)GetDlgItem(IDC_EDIT_FAIRY_LVL);
		CString cs_max_chars;
		cs_max_chars.Format(L"%d", HWLSaveEdit::HWLFairy::fairyLVLMax);
		e_test->SetLimitText(cs_max_chars.GetLength() + 1);
		GetDlgItemText(IDC_EDIT_FAIRY_LVL, test);
		int i_test = _wtoi(test);

		if (i_test > HWLSaveEdit::HWLFairy::fairyLVLMax)
		{
			test.Format(L"%d", HWLSaveEdit::HWLFairy::fairyLVLMax);
			SetDlgItemText(IDC_EDIT_FAIRY_LVL, test);
			e_test->SetLimitText(cs_max_chars.GetLength());
		}

	}
}


void CZeldaEditFairyDlg::OnEnChangeEditFairyTrust()
{
	if (save != nullptr)
	{
		CString test;
		CEdit *e_test = (CEdit*)GetDlgItem(IDC_EDIT_FAIRY_TRUST);
		CString cs_max_chars;
		cs_max_chars.Format(L"%d", HWLSaveEdit::HWLFairy::fairyTrustMax);
		e_test->SetLimitText(cs_max_chars.GetLength() + 1);
		GetDlgItemText(IDC_EDIT_FAIRY_TRUST, test);
		int i_test = _wtoi(test);

		if (i_test > HWLSaveEdit::HWLFairy::fairyTrustMax)
		{
			test.Format(L"%d", HWLSaveEdit::HWLFairy::fairyTrustMax);
			SetDlgItemText(IDC_EDIT_FAIRY_TRUST, test);
			e_test->SetLimitText(cs_max_chars.GetLength());
		}

	}
}


void CZeldaEditFairyDlg::OnEnChangeEditFairyIterator()
{
	if (save != nullptr)
	{
		CString test;
		CEdit *e_test = (CEdit*)GetDlgItem(IDC_EDIT_FAIRY_ITERATOR);
		CString cs_max_chars;
		cs_max_chars.Format(L"%d", HWLSaveEdit::HWLFairy::fairyIteratorMax);
		e_test->SetLimitText(cs_max_chars.GetLength() + 1);
		GetDlgItemText(IDC_EDIT_FAIRY_ITERATOR, test);
		int i_test = _wtoi(test);

		if (i_test > HWLSaveEdit::HWLFairy::fairyIteratorMax)
		{
			test.Format(L"%d", HWLSaveEdit::HWLFairy::fairyIteratorMax);
			SetDlgItemText(IDC_EDIT_FAIRY_ITERATOR, test);
			e_test->SetLimitText(cs_max_chars.GetLength());
		}

	}
}


void CZeldaEditFairyDlg::OnMenuEditCharactersWeapons()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditCharaWeaponsDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}



void CZeldaEditFairyDlg::OnMenuMainExit()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditFairyDlg::OnOK();

}


void CZeldaEditFairyDlg::OnMenuEditCharactersOverview()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditCharaOverviewDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}