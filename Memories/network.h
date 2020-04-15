#pragma once
#include <sys/return_code.h>
#include <sys/socket.h>
#include <sysutil/sysutil_oskdialog.h>
#include <sysutil/sysutil_msgdialog.h>
char *CreateBack;
bool CreateAccountBool;
int sleep(int msec);
#pragma region Converter
bool cstrcmp(const char* s1, const char* s2)
{
	while (*s1 && (*s1 == *s2))
		s1++, s2++;
	if (*(const unsigned char*)s1 - *(const unsigned char*)s2 == 0)
		return true;
	else
		return false;
}
bool isNumericChar(char x)
{
	return (x >= '0' && x <= '9') ? true : false;
}
int StoI(char *str)
{
	if (*str == NULL)
		return 0;

	int res = 0,
		sign = 1,
		i = 0;

	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}
	for (; str[i] != '\0'; ++i)
	{
		if (isNumericChar(str[i]) == false)
			return 0;
		res = res * 10 + str[i] - '0';
	}
	return sign*res;
}
char *ItoS(int num, bool isX = true)
{
	char buf[30];
	sprintf(buf, isX ? "0x%8X" : "%i", num);
	return buf;
}
char* FtoS(float input = 0.0f, float X = 100)
{
	float Backup = input;
	char returnvalue[64];
	int wholenumber = (int)input;
	input -= wholenumber;
	input *= X;
	if (Backup < 0)
	{
		input *= -1; 
		wholenumber *= -1;
	}
	sprintf(returnvalue, "%d.%d", wholenumber, (int)input);
	return returnvalue;
}
#pragma endregion
#define SERVER_PORT htons(80)

char *ReturnPSID()
{
	char MacBuf[300];
	CellSsOpenPSID psid;
	system_call_1(SYS_SS_GET_OPEN_PSID, (uint64_t)&psid);
	sprintf(MacBuf, "%llX%llX", psid.high, psid.low);
	return MacBuf;
}

namespace network
{
	int sendRequest_main(const char*);
	int sendRequest(const char* url)
	{
		int ret, ret2;

		ret = cellSysmoduleLoadModule(CELL_SYSMODULE_HTTP);
		if (ret != CELL_SYSMODULE_LOADED) {
		return ret;
		}

		ret = sys_net_initialize_network();
		if (ret != CELL_OK) {
			return ret;
		}

		ret2 = sendRequest_main(url);

		ret = sys_net_finalize_network();
		if (ret != CELL_OK) {
			return ret;
		}

		ret = cellSysmoduleUnloadModule(CELL_SYSMODULE_HTTP);
		if (ret != CELL_OK) {
			return ret;
		}

		return ret2;
	}

#define RECV_BUFFER_SIZE 100
#define HTTP_POOL_SIZE 8192
	static char responseBuf[RECV_BUFFER_SIZE];
	int sendRequest_main(const char* url)
	{
		int ret;
		void* httpPool, *uriPool;
		CellHttpClientId clientId;
		CellHttpUri uri;
		CellHttpTransId transId;
		size_t poolSize, localRecv;
		uint64_t length, recvd;
		bool has_cl = true;

		httpPool = _sys_malloc(HTTP_POOL_SIZE);
		if (httpPool == NULL) {
			ret = -1;
			goto end;
		}

		ret = cellHttpInit(httpPool, HTTP_POOL_SIZE);
		if (ret != CELL_OK) {
			goto end;
		}

		ret = cellHttpCreateClient(&clientId);

		if (ret != CELL_OK) {
			goto end;
		}

		ret = cellHttpUtilParseUri(NULL, url, NULL, 0, &poolSize);
		if (ret != CELL_OK) {
				goto end;
		}

		uriPool = _sys_malloc(poolSize);
		if (uriPool == NULL) {
			goto end;
		}

		ret = cellHttpUtilParseUri(&uri, url, uriPool, poolSize, NULL);
		if (ret != CELL_OK) {
			_sys_free(uriPool);
			uriPool = NULL;
			goto end;
		}

		ret = cellHttpCreateTransaction(&transId, clientId, CELL_HTTP_METHOD_GET, &uri);
		if (ret != CELL_OK) {
			goto end;
		}

		ret = cellHttpSendRequest(transId, NULL, 0, NULL);
		if (ret != CELL_OK) {
			goto end;
		}
		int code;
		ret = cellHttpResponseGetStatusCode(transId, &code);
		if (ret != CELL_OK) {
				goto end;
		}
		
		ret = cellHttpResponseGetContentLength(transId, &length);
		if (ret != CELL_OK) {
			if (ret == CELL_HTTP_ERROR_NO_CONTENT_LENGTH) {
				has_cl = false;
			}
			else {
				goto end;
			}
		}

		recvd = 0;
		while (!has_cl || recvd < length) {
			ret = cellHttpRecvResponse(transId, responseBuf, RECV_BUFFER_SIZE - 1, &localRecv);
			if (ret != CELL_OK) {
				goto end;
			}
			else if (localRecv == 0) break;
			recvd += localRecv;
			responseBuf[localRecv] = '\0';
		}

		//printf(responseBuf);
		//printf("\n");

		ret = 0;

	end:
		if (transId) {
			cellHttpDestroyTransaction(transId);
			transId = 0;
		}
		if (clientId) {
			cellHttpDestroyClient(clientId);
			clientId = 0;
		}
		cellHttpEnd();
		_sys_free(httpPool);

		return ret;
	}
	char* getResponse(void)
	{
		return responseBuf;
	}
}

namespace Dialog
{
	bool Finished = false;
	bool YESNO = false;

	enum {
		MODE_IDLE = 0,
		MODE_ERRORCODE_DIALOG_TEST,
		MODE_STRING_OK,
		MODE_STRING_YESNO,
		MODE_STRING_DIALOG_3,
		MODE_STRING_DIALOG_4,
		MODE_STRING_DIALOG_5,
		MODE_CHECK_PROGRESSBAR_1,
		MODE_RUNNING,
		MODE_CHECK_TIMEOUT,
		MODE_TIMEOUT_NEXT,
		MODE_EXIT
	};

	static int msgdialog_mode = MODE_IDLE;

	static void cb_dialogText1(int button_type, void *userdata)
	{
		switch (button_type) {

		case CELL_MSGDIALOG_BUTTON_OK:
			msgdialog_mode = MODE_EXIT;
			break;
		case CELL_MSGDIALOG_BUTTON_ESCAPE:
			msgdialog_mode = MODE_EXIT;
			break;

		default:
			msgdialog_mode = MODE_EXIT;
			break;
		}
	}

	static void cb_dialogText3(int button_type, void *userdata)
	{
		switch (button_type) {
		default:
			msgdialog_mode = MODE_EXIT;
			break;
		}
	}
	void _sleep(usecond_t time)
	{
		sys_timer_usleep(time * 1000);
	}
	int _console_write(const char * s)
	{
		uint32_t len;
		system_call_4(403, 0, (uint64_t)s, std::strlen(s), (uint64_t)&len);
		return_to_user_prog(int);
	}
	void Show(char* msg)
	{

		unsigned int type = CELL_MSGDIALOG_TYPE_SE_TYPE_ERROR
			| CELL_MSGDIALOG_TYPE_BG_INVISIBLE
			| CELL_MSGDIALOG_TYPE_BUTTON_TYPE_OK
			| CELL_MSGDIALOG_TYPE_DISABLE_CANCEL_ON
			| CELL_MSGDIALOG_TYPE_DEFAULT_CURSOR_OK;


		switch (msgdialog_mode)
		{
		case MODE_IDLE:
			break;

		case MODE_STRING_OK:
			cellMsgDialogOpen2(type, msg, cb_dialogText1, NULL, NULL);
			msgdialog_mode = MODE_EXIT;
			break;

		case MODE_EXIT:
			cellMsgDialogClose((float)5);
			break;

		default:
			break;

		}

		while (Dialog::msgdialog_mode != Dialog::MODE_EXIT) {}  //wait for the dialog to end :P
	}

	void Showprogress(const char* msg, const char* Secondmessage = "", bool stop = false, bool second = false)
	{
		unsigned int type = CELL_MSGDIALOG_TYPE_SE_TYPE_NORMAL
			| CELL_MSGDIALOG_TYPE_BG_VISIBLE
			//| CELL_MSGDIALOG_TYPE_BG_INVISIBLE
			| CELL_MSGDIALOG_TYPE_BUTTON_TYPE_NONE
			| CELL_MSGDIALOG_TYPE_DISABLE_CANCEL_ON
			| CELL_MSGDIALOG_TYPE_DEFAULT_CURSOR_NONE
			//| CELL_MSGDIALOG_TYPE_PROGRESSBAR_DOUBLE;
			| CELL_MSGDIALOG_TYPE_PROGRESSBAR_SINGLE;
		cellMsgDialogOpen2(type, msg, NULL, NULL, NULL);
		cellMsgDialogProgressBarSetMsg(CELL_MSGDIALOG_PROGRESSBAR_INDEX_DOUBLE_UPPER, Secondmessage);
		/*for (int i = 0; i < 100; i++)
		{
			
			_sleep(time);
		}*/
		if (!second)
		{
			_sleep(3000);
			cellMsgDialogProgressBarInc(CELL_MSGDIALOG_PROGRESSBAR_INDEX_SINGLE, 40);
			_sleep(3000);
			cellMsgDialogProgressBarInc(CELL_MSGDIALOG_PROGRESSBAR_INDEX_SINGLE, 20);
			_sleep(3000);
			if (!stop)
			{
				cellMsgDialogProgressBarInc(CELL_MSGDIALOG_PROGRESSBAR_INDEX_SINGLE, 40);
				_sleep(3000);
				Finished = true;
				cellMsgDialogClose(2);
			}
		}
		else
		{
			_sleep(3000);
			cellMsgDialogProgressBarInc(CELL_MSGDIALOG_PROGRESSBAR_INDEX_SINGLE, 40);
			_sleep(6000);
			cellMsgDialogProgressBarInc(CELL_MSGDIALOG_PROGRESSBAR_INDEX_SINGLE, 30);
			if (CreateAccountBool)
			{
				cellMsgDialogProgressBarInc(CELL_MSGDIALOG_PROGRESSBAR_INDEX_SINGLE, 30);
				cellMsgDialogClose(2);
			}
		}
	}

	static void cb_dialogText2(int button_type, void *userdata)
	{
		switch (button_type) {

		case CELL_MSGDIALOG_BUTTON_YES:
			YESNO = true;
			msgdialog_mode = MODE_EXIT;
			Finished = true;
			break;

		case CELL_MSGDIALOG_BUTTON_NO:
			msgdialog_mode = MODE_EXIT;
			Finished = true;
			break;

		case CELL_MSGDIALOG_BUTTON_ESCAPE:
			msgdialog_mode = MODE_EXIT;
			Finished = true;
			break;

		default:
			break;
		}
	}


	void ShowYESNO(char* msg)
	{
		int ret = 0;
		unsigned int type = CELL_MSGDIALOG_TYPE_SE_TYPE_NORMAL
			| CELL_MSGDIALOG_TYPE_BG_INVISIBLE
			| CELL_MSGDIALOG_TYPE_BUTTON_TYPE_YESNO
			| CELL_MSGDIALOG_TYPE_DISABLE_CANCEL_ON
			| CELL_MSGDIALOG_TYPE_DEFAULT_CURSOR_YES;


		switch (msgdialog_mode)
		{
		case MODE_IDLE:
			break;

		case MODE_STRING_YESNO:
			cellMsgDialogOpen2(type, msg, cb_dialogText2, NULL, NULL);
			msgdialog_mode = MODE_RUNNING;
			break;

		case MODE_EXIT:
			cellMsgDialogClose((float)1);
			break;

		default:
			break;

		}


	}

	void End()
	{
		Finished = false;
		YESNO = false;
	}

	void ShowText(const char* msg)
	{
		if (*msg == 0)return;
		unsigned int type =
			CELL_MSGDIALOG_TYPE_SE_TYPE_NORMAL |
			CELL_MSGDIALOG_TYPE_SE_MUTE_ON |
			CELL_MSGDIALOG_TYPE_BG_VISIBLE |
			CELL_MSGDIALOG_TYPE_BUTTON_TYPE_NONE |
			CELL_MSGDIALOG_TYPE_DISABLE_CANCEL_ON |
			CELL_MSGDIALOG_TYPE_DEFAULT_CURSOR_NONE |
			CELL_MSGDIALOG_TYPE_PROGRESSBAR_SINGLE;
		cellMsgDialogOpen2(type, msg, cb_dialogText1, NULL, NULL);
	}

	void Close()
	{
		cellMsgDialogClose(500.0f);
		sleep(1000);
	}

	void SetProgressText(const char* msg)
	{
		if (*msg == 0)return;
		cellMsgDialogProgressBarSetMsg(0, msg);
		cellMsgDialogProgressBarInc(0, 0);
	}

	void SetProgressInc(unsigned int delta)
	{
		cellMsgDialogProgressBarInc(0, delta);
	}
}

namespace Keyboard
{
	enum {
		MODE_IDLE = 0,
		MODE_OPEN,
		MODE_RUNNING,
		MODE_CLOSE,
		MODE_ENTERED,
		MODE_CANCELED,
		SET_ABORT_TIMER,
		CHANGE_PANEL_MODE,
		CHANGE_SCALE,
		SET_CALLBACK,
		MODE_EXIT,
		START_DIALOG_TYPE,
		START_SEPARATE_TYPE_1,
		START_SEPARATE_TYPE_2,
	};
	static int oskdialog_mode = MODE_IDLE;

	int getkbLen(char* str)
	{
		int nullCount = 0;
		int i = 0; //num of chars..
		for (i = 0; i < 64; i++)
		{
			if (nullCount == 2) { break; }
			if (*(str + i) == 0x00) { nullCount++; }
			else { nullCount = 0; }
		}
		return i;
	}
	void makekbStr(char* str, char* dest, int len)
	{
		int nulls = 0;
		for (int i = 0; i < len; i++)
		{
			if (*(str + i) == 0x00) { nulls++; }
			else { *(dest + i - nulls) = *(str + i); }
		}
		*(dest + len + 1 - nulls) = 0x00;  //make sure its nulled...
	}

	static void sysutil_callback(uint64_t status, uint64_t param, void *userdata)
	{
		(void)param;
		(void)userdata;
		int ret = 0;

		switch (status) {
		case CELL_SYSUTIL_OSKDIALOG_LOADED:
			break;
		case CELL_SYSUTIL_OSKDIALOG_FINISHED:
			oskdialog_mode = MODE_CLOSE;
			break;
		case CELL_SYSUTIL_OSKDIALOG_UNLOADED:
			break;
		case CELL_SYSUTIL_REQUEST_EXITGAME:
			oskdialog_mode = MODE_EXIT;
			break;
		case CELL_SYSUTIL_DRAWING_BEGIN:
			break;
		case CELL_SYSUTIL_DRAWING_END:
			break;
		case CELL_SYSUTIL_OSKDIALOG_INPUT_ENTERED:
			oskdialog_mode = MODE_ENTERED;
			break;
		case CELL_SYSUTIL_OSKDIALOG_INPUT_CANCELED:
			oskdialog_mode = MODE_CANCELED;
			break;
		case CELL_SYSUTIL_OSKDIALOG_INPUT_DEVICE_CHANGED:
			break;
		case CELL_SYSUTIL_OSKDIALOG_DISPLAY_CHANGED:
			break;
		case CELL_SYSUTIL_SYSTEM_MENU_CLOSE:

			break;
		case CELL_SYSUTIL_SYSTEM_MENU_OPEN:
			break;
		default:
			break;
		}
	}
	int kb_console_write(const char * s)
	{
		uint32_t len;
		system_call_4(403, 0, (uint64_t)s, std::strlen(s), (uint64_t)&len);
		return_to_user_prog(int);
	}
	int keyboard(char* dest, char* INIT_TEXT, char* MESSAGE)
	{


#pragma region Declarations

		int ret;
		CellOskDialogInputFieldInfo inputFieldInfo;
		inputFieldInfo.message = (uint16_t*)MESSAGE;
		inputFieldInfo.init_text = (uint16_t*)INIT_TEXT;
		inputFieldInfo.limit_length = CELL_OSKDIALOG_STRING_SIZE;


		CellOskDialogCallbackReturnParam OutputInfo;
		OutputInfo.result = CELL_OSKDIALOG_INPUT_FIELD_RESULT_OK;
		OutputInfo.numCharsResultString = 32;

		uint16_t Result_Text_Buffer[CELL_OSKDIALOG_STRING_SIZE + 1];
		OutputInfo.pResultString = Result_Text_Buffer;

		ret = cellOskDialogSetKeyLayoutOption(CELL_OSKDIALOG_10KEY_PANEL | CELL_OSKDIALOG_FULLKEY_PANEL);


		CellOskDialogPoint pos;
		pos.x = 0.0;  pos.y = 0.0;
		int32_t LayoutMode = CELL_OSKDIALOG_LAYOUTMODE_X_ALIGN_CENTER | CELL_OSKDIALOG_LAYOUTMODE_Y_ALIGN_TOP;
		ret = cellOskDialogSetLayoutMode(LayoutMode);


		CellOskDialogParam dialogParam;
		dialogParam.allowOskPanelFlg = CELL_OSKDIALOG_PANELMODE_KOREAN |
			CELL_OSKDIALOG_PANELMODE_ALPHABET |
			CELL_OSKDIALOG_PANELMODE_NUMERAL_FULL_WIDTH |
			CELL_OSKDIALOG_PANELMODE_NUMERAL |
			CELL_OSKDIALOG_PANELMODE_JAPANESE |
			CELL_OSKDIALOG_PANELMODE_JAPANESE_KATAKANA |
			CELL_OSKDIALOG_PANELMODE_ENGLISH;
		/*E Panel to display first */
		dialogParam.firstViewPanel = CELL_OSKDIALOG_PANELMODE_ALPHABET;
		/* E Initial display position of the on-screen keyboard dialog */
		dialogParam.controlPoint = pos;
		/*E Prohibited operation flag(s) (ex. CELL_OSKDIALOG_NO_SPACE) */
		dialogParam.prohibitFlgs = 0;


#pragma endregion

		sys_timer_usleep(16 * 1000);
		ret = cellSysutilCheckCallback();



		if (oskdialog_mode == MODE_OPEN)
		{
			if (cellSysutilRegisterCallback(0, sysutil_callback, NULL) != 0) { kb_console_write("\nCouldn't register the keyboard !\n"); }
			ret = cellOskDialogLoadAsync(SYS_MEMORY_CONTAINER_ID_INVALID, &dialogParam, &inputFieldInfo);
			oskdialog_mode = MODE_RUNNING;
		}

		if (oskdialog_mode == MODE_ENTERED)
		{
			ret = cellOskDialogGetInputText(&OutputInfo);
			oskdialog_mode = MODE_RUNNING;
		}
		if (oskdialog_mode == MODE_CLOSE)
		{
			ret = cellOskDialogUnloadAsync(&OutputInfo);

			int strLen = getkbLen((char*)(*(&OutputInfo.pResultString)));
			makekbStr((char*)(*(&OutputInfo.pResultString)), dest, strLen);
			inputFieldInfo.init_text = (uint16_t*)INIT_TEXT;
			if (cellSysutilUnregisterCallback(0) != 0) { kb_console_write("\nCouldn't unload the keyboard !\n"); }
			oskdialog_mode = MODE_EXIT;
		}

		return 0;
	}
};
