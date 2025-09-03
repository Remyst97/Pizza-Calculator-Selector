
// Pizza_Calc_SelectDlg.h : header file
//

#pragma once


// CPizzaCalcSelectDlg dialog
class CPizzaCalcSelectDlg : public CDialogEx
{
// Construction
public:
	CPizzaCalcSelectDlg(CWnd* pParent = nullptr);	// standard constructor
	virtual ~CPizzaCalcSelectDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PIZZA_CALC_SELECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	// Member variables for controls
	int m_nGuests;
	CEdit m_editGuests;
	CStatic m_staticOutput;
	CButton m_btnCalculate;

	afx_msg void OnBnClickedCalculate();

	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	int guestslimit(); // Declare the function
	int pizzaCalculation();
	afx_msg void OnEnChangeGuests();
	void UpdateToppingPies(int editControlID, int& toppingPies);
	void HandleTopping(int checkboxID, int& toppingPies);
	int ValidatePies(int pies, int& totalPiesLimit, const CString& toppingName);
	void UpdateRemainingPies();
	afx_msg void OnBnClickedCalculateTotal();
	void CalculatePiesAndCost();

private:
	int m_totalPiesLimit;
	int m_cheesePies;
	int m_extraCheesePies;
	int m_pepperoniPies;
	int m_chickenPies;

	CButton m_checkCheese;
	CEdit m_editCheesePies;
	CButton m_checkextraCheese;
	CEdit m_editextraCheesePies;
	CButton m_checkPepperoni;
	CEdit m_editPepperoniPies;
	CButton m_checkChicken;
	CEdit m_editChickenPies;

	CStatic m_staticRemainingPies;
	CStatic m_staticTotalCost;
};

