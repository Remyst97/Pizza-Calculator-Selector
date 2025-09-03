
// Pizza_Calc_SelectDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Pizza_Calc_Select.h"
#include "Pizza_Calc_SelectDlg.h"
#include "afxdialogex.h"
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPizzaCalcSelectDlg dialog



CPizzaCalcSelectDlg::CPizzaCalcSelectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PIZZA_CALC_SELECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_totalPiesLimit =0; // Set your initial limit here
	m_cheesePies = 0;
	m_extraCheesePies = 0;
	m_pepperoniPies = 0;
	m_chickenPies = 0;
}

CPizzaCalcSelectDlg::~CPizzaCalcSelectDlg()
{
}

void CPizzaCalcSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_guest_in, m_nGuests);
	DDX_Control(pDX, IDC_guest_in, m_editGuests);
	DDX_Control(pDX, IDC_BUTTON_calc, m_btnCalculate);
	DDX_Control(pDX, IDC_pies, m_staticOutput);
}

BEGIN_MESSAGE_MAP(CPizzaCalcSelectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_guest_in, &CPizzaCalcSelectDlg::OnEnChangeGuests)
	ON_BN_CLICKED(IDC_BUTTON_calc, &CPizzaCalcSelectDlg::OnBnClickedCalculate)
	ON_BN_CLICKED(IDC_BUTTON_total_cost, &CPizzaCalcSelectDlg::OnBnClickedCalculateTotal)
END_MESSAGE_MAP()

BOOL CPizzaCalcSelectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	m_checkCheese.SubclassDlgItem(IDC_Cheese, this);
	m_checkextraCheese.SubclassDlgItem(IDC_Extra, this);
	m_checkPepperoni.SubclassDlgItem(IDC_pepperoni, this);
	m_checkChicken.SubclassDlgItem(IDC_chicken, this);
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPizzaCalcSelectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPizzaCalcSelectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPizzaCalcSelectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CPizzaCalcSelectDlg::guestslimit()
{
	int value;

	while (true) {
		CString inputStr;
		GetDlgItemText(IDC_guest_in, inputStr); // Assuming IDC_guest_in is the ID of your Edit Control

		// Convert the CString to an integer
		if (_stscanf_s(inputStr, _T("%d"), &value) == 1 && value >= 0 && value <= 1000) {
			break; // Exit the loop if the input is valid
		}
		else {
			// Display an error message
			MessageBox(_T("Invalid input. Please enter a valid number between 0 and 1000."), _T("Error"), MB_OK | MB_ICONERROR);

			// Clear the contents of the edit control
			SetDlgItemText(IDC_guest_in, _T(""));

			return -1; // Or some other value indicating an error
		}
	}

	return value;
}

void CPizzaCalcSelectDlg::OnEnChangeGuests()
{
	UpdateToppingPies(IDC_cheese_pies, m_cheesePies);
	UpdateToppingPies(IDC_extra_pies, m_extraCheesePies);
	UpdateToppingPies(IDC_pepper_pies, m_pepperoniPies);
	UpdateToppingPies(IDC_chicken_pies, m_chickenPies);

	// Perform other actions or calculations as needed...
}

void CPizzaCalcSelectDlg::UpdateToppingPies(int editControlID, int& toppingPies)
{
	CEdit* pEditTopping = (CEdit*)GetDlgItem(editControlID);

	if (pEditTopping)
	{
		CString strPies;
		pEditTopping->GetWindowText(strPies);

		// Convert the text to an integer
		int numberOfPies = _ttoi(strPies);

		// Update the toppingPies variable
		toppingPies = numberOfPies;

		// Your additional logic for this topping...
	}
}

int CPizzaCalcSelectDlg::pizzaCalculation() {
	// Get the number of guests from the edit control

		// Perform calculations
		int noOfGuests = guestslimit();
		if (noOfGuests == -1) {
			// Validation failed, handle the error if needed
			return 0;
		}

		// Perform calculations
		int noOfSlices = noOfGuests * 3;
		int pizzaPies = ceil(static_cast<float>(noOfSlices) / 8);

		return pizzaPies;

}

void CPizzaCalcSelectDlg::OnBnClickedCalculate()
{
	// Get the number of guests from the edit control
	if (UpdateData(TRUE)) {
		int pizzaPies = pizzaCalculation();

		// Display the result in the static text control
		CString strOutput;
		strOutput.Format(_T("Total number of Pizza Pies = %.2d"), pizzaPies);
		m_staticOutput.SetWindowText(strOutput);

		HandleTopping(IDC_Cheese, m_cheesePies);
		HandleTopping(IDC_Extra, m_extraCheesePies);
		HandleTopping(IDC_pepperoni, m_pepperoniPies);
		HandleTopping(IDC_chicken, m_chickenPies);
	}

	

	float cheese = 14.0;
	float extra = 17.25; // Update with the actual cost of extra cheese
	float pepperoni = 17.25;
	float chicken = 21.50;

	// Calculate total price
	float totalPrice = (cheese * m_cheesePies) + (extra * m_extraCheesePies) + (pepperoni * m_pepperoniPies) + (chicken * m_chickenPies);

	// Display the total cost in a static text control
	CString strTotalCost;
	strTotalCost.Format(_T("Total Cost: $%.2f"), totalPrice);
	GetDlgItem(IDC_STATIC_total_cost)->SetWindowText(strTotalCost);

	// Update the remaining pies
	UpdateRemainingPies();

	// Read the number of pies for each topping
	int cheesePies = m_checkCheese.GetCheck() == BST_CHECKED ? m_cheesePies : 0;
	int extraCheesePies = m_checkextraCheese.GetCheck() == BST_CHECKED ? m_extraCheesePies : 0;
	int pepperoniPies = m_checkPepperoni.GetCheck() == BST_CHECKED ? m_pepperoniPies : 0;
	int chickenPies = m_checkChicken.GetCheck() == BST_CHECKED ? m_chickenPies : 0;

}


void CPizzaCalcSelectDlg::HandleTopping(int checkboxID, int& toppingPies)
{
	if (IsDlgButtonChecked(checkboxID)) {
		int pies = GetDlgItemInt(checkboxID + 1); // Assuming edit control ID is consecutive to checkbox ID
		ValidatePies(pies, toppingPies, _T("Topping"));
	}
	else {
		toppingPies = 0;
	}
}

int CPizzaCalcSelectDlg::ValidatePies(int pies, int& totalPiesLimit, const CString& toppingName)
{
	if (pies > totalPiesLimit) {
		MessageBox(_T("Error: The total number of pies exceeds the limit."), _T("Error"), MB_OK | MB_ICONERROR);
		return -1;
	}

	totalPiesLimit -= pies;
	return pies;
}

void CPizzaCalcSelectDlg::UpdateRemainingPies()
{
	// Calculate and display the remaining pies
	int pizzaPies = pizzaCalculation();
	int remainingPies = pizzaPies - (m_cheesePies + m_extraCheesePies + m_pepperoniPies + m_chickenPies);

	CString strRemainingPies;
	strRemainingPies.Format(_T("Remaining Pies: %d"), remainingPies);
	GetDlgItem(IDC_STATIC_remaining_pies2)->SetWindowText(strRemainingPies);
}
void CPizzaCalcSelectDlg::OnBnClickedCalculateTotal()
{
	CalculatePiesAndCost();
}

void CPizzaCalcSelectDlg::CalculatePiesAndCost()
{
	float cheese = 14.0;
	float extra = 17.25;
	float pepperoni = 17.25;
	float chicken = 21.50;

	// Calculate total price
	float totalPrice = (cheese * m_cheesePies) + (extra * m_extraCheesePies) + (pepperoni * m_pepperoniPies) + (chicken * m_chickenPies);

	// Display the total cost in a static text control
	CString strTotalCost;
	strTotalCost.Format(_T("Total Cost: $%.2f"), totalPrice);
	GetDlgItem(IDC_total_cost)->SetWindowText(strTotalCost);

	// Calculate remaining pies
	UpdateRemainingPies();
}


