#pragma once

#include "PGLFirstData.h"
#include "PGLVMError.h"

class PGLVMThread;

enum class PGLOpcode : short
{
	NOP, // �ƹ� �͵� ���� ����
	PUSH, // ���ͷ�/�������� %1�� ���ÿ� �ִ´�
	STORE, // ���ÿ��� �ڷḦ ���� �������� %1�� �����Ѵ�
	COPY, // ���̽����� + %1��ġ�� �ִ� �ڷḦ ���ÿ� �ִ´�
	WRITE, // ���ÿ��� �ڷ� �ϳ��� ���� ���̽����� + %1��ġ�� �����
	POP, // ���ÿ��� %1���� �ڷḦ ������
	CALL, // ���ÿ��� �ּҸ� ������, %1���� ���ڸ� ����Ͽ� �Լ� ȣ��
	THISCALL, // ���ÿ��� �ּҸ� ������ this�� %1���� ���ڸ� ����Ͽ� �Լ� ȣ��
	RETURN, // ��ȯ���� %1���� �����ϰ�, ���� �ּҷ� ����
	YIELD, // ��ȯ���� %1���� �����ϰ�, �� ������ ������ �����ϰ�, �θ� �����忡�� ������ �ѱ��
	ADD, // ���ÿ��� 2���� �̾� ���� ����� ���ÿ� �ִ´�
	SUB, // ���ÿ��� 2���� �̾� �� ����� ���ÿ� �ִ´�
	MUL, // ���ÿ��� 2���� �̾� ���� ����� ���ÿ� �ִ´�
	DIV, // ���ÿ��� 2���� �̾� ���� ����� ���ÿ� �ִ´�
	MOD,
	POW, // ���ÿ��� 2���� �̾� n���� ����� ���ÿ� �ִ´�
	SIGN, // ���ÿ��� 1���� �̾� ��ȣ�� �����Ͽ� ���ÿ� �ִ´�
	EQ,
	NEQ,
	GT,
	GTE,
	LS,
	LSE,
	AND,
	OR,
	NOT,
	JMP, // %1������ �����Ѵ�
	UNLESSJMP, // ���ÿ��� 1���� �̾�, �� ���� �����̸�,  %1������ �����Ѵ�
	PUSHNULL, // ���ÿ� null�� �ִ´�
	ASSEMBLE, // ���ÿ��� %1���� �̾� �迭�� ����� ���ÿ� �ִ´�
	NEWDICT, // ���ÿ��� 2* %1���� �̾�, ���ʷ� Ű, ������ �ϴ� ������ ����� ���ÿ� �ִ´�
	AT, // ���ÿ��� �迭 Ȥ�� ������ Ű�� �̾�, Ű�� �ش��ϴ� ���� ���ÿ� �ִ´�
	LEN, // ���ÿ��� �迭 Ȥ�� ������ �̰� �� ũ�⸦ ���Ͽ� ���ÿ� �ִ´�
	ATD, // ���ÿ��� �迭�� �̰�, %1��° ���Ҹ� ���ÿ� �ִ´�
	MAKECLOSURE, // ���ÿ��� �Լ� �ּҿ� �迭�� ���� Ŭ������ ����, ����� ���ÿ� �ִ´�
	SET, // ���ÿ��� �ڷ�� �迭 Ȥ�� ������ Ű�� �̾�, Ű�� �ش��ϴ� ���� �ڷ�� �����Ѵ�
	SETD, // ���ÿ��� �ڷ�� �迭�� �̾�, �� �迭�� %1��° ���ҷ� �����Ѵ�
	REF, // ���ÿ��� �ڷḦ �̾�, ���۷����Ͽ� ���ÿ� �ִ´�
	DEREF, // ���ÿ��� �ڷḦ �̾�, ���۷����Ͽ� ���ÿ� �ִ´�
	COPYDEREF, // COPY + DEREF
	SETDDEREF, // ���ÿ��� �ڷ�� �迭�� �̾�, �� �迭�� %1��° ������ ���۷����� �����Ѵ�
	WRITEDEREF, // ���ÿ��� �ڷ� �ϳ��� ���� ���̽����� + %1��ġ�� ���۷����� �����Ѵ�
	PUSHBEGIN, // ���� ����⿡ ��ġ�� �迭 Ȥ�� �������� ��ȸ ù ������ ������ ��� �ڷḦ ���ÿ� �ִ´�
	ISNOTEND, // ���� ����⿡ ��ġ�� ��ȸ ������ ���� �ٴٶ����� ����, �ƴϸ� ���� ���ÿ� �ִ´�
	NEXT, // ���� ����⿡ ��ġ�� ��ȸ ������ �������� �����Ѵ�
	PUSHKEYVAL, // ���� ����⿡ ��ġ�� ��ȸ �������� Ű�� ���� �̾� ���ÿ� �ִ´�
	FIND, // ���ÿ��� �迭 Ȥ�� ������ Ű�� �̿� Ű�� �ش��ϴ� ���� ���ÿ� �ִ´�. ���� ���� ��� ��Ÿ�� ����
	FINDP, // ���ÿ��� �迭 Ȥ�� ������ Ű�� �̿� Ű�� �ش��ϴ� ���� ���ÿ� �ְ� �迭 Ȥ�� ������ �ٽ� �ִ´�. ���� ���� ��� ��Ÿ�� ����.
	THROW, // ���� ����⸦ ���� ��ü�� �Ͽ� ���ܸ� ������
	TRY, // %1������ ���� ó����ƾ���� ����Ѵ�
	TRYEXIT, // ���� ó����ƾ�� �����Ѵ�
	POPTO, // ���̽����� ���� %1���� �ڷᰡ ������ �������� ������.
};

#define PGL_ERROR -2
#define PGL_OK 0
#define PGL_ENTRY 1
#define PGL_YIELD 2
#define PGL_RUNERR 3
#define PGL_RUNNING 4
#define PGL_THROW 5

typedef int (*PGL_CFunc)(void*);

struct PGLVMDebugInfo
{
	int line;
};

struct FinalData
{
	vector<shared_ptr<PGLCompoundData>> globLiteral;
	vector<string> globDebugInfo;
	vector<short> code;
	vector<PGLVMDebugInfo> debugInfo;
};

class PGLVM
{
	friend class PGLVMThread;
protected:
	vector<short> m_codes;
	vector<PGLVMDebugInfo> m_debugInfo;
	vector<shared_ptr<PGLCompoundData>> m_literal;
	vector<string> m_globDebugInfo;
public:
	PGLVM(const FinalData& fd);
	~PGLVM();
	PGLVMThread* NewThread();
	string _GetDisassembly(const short* codes, size_t size, size_t rel);
	string GetDisassembly(const char* funcName = nullptr);
	shared_ptr<PGLCompoundData> GetGlobalValue(const char* name);
	int SetGlobalValue(const char* name, const shared_ptr<PGLCompoundData>& data);
};

class PGLVMThread
{
protected:
	int m_pc;
	vector<shared_ptr<PGLCompoundData>> m_stack;
	vector<int> m_stackBase;
	vector<int> m_callstack;
	vector<int> m_catchAddr;
	PGLVM* m_mainVM;
	string m_err;
	size_t m_retCnt;
	shared_ptr<PGLCompoundData> m_yieldCF;
	void* m_userPtr;
	int m_state;

	int CallProc(const shared_ptr<PGLCompoundData>& func, int operand, bool thiscall = false);
public:
	int ProcNOP();
	int ProcPUSH();
	int ProcSTORE();
	int ProcCOPY();
	int ProcWRITE();
	int ProcPOP();
	int ProcCALL();
	int ProcTHISCALL();
	int ProcRETURN();
	int ProcYIELD();
	int ProcADD();
	int ProcSUB();
	int ProcMUL();
	int ProcDIV();
	int ProcMOD();
	int ProcPOW();
	int ProcSIGN();
	int ProcEQ();
	int ProcNEQ();
	int ProcGT();
	int ProcGTE();
	int ProcLS();
	int ProcLSE();
	int ProcAND();
	int ProcOR();
	int ProcNOT();
	int ProcJMP();
	int ProcUNLESSJMP();
	int ProcPUSHNULL();
	int ProcASSEMBLE();
	int ProcNEWDICT();
	int ProcAT();
	int ProcLEN();
	int ProcATD();
	int ProcMAKECLOSURE();
	int ProcSET();
	int ProcSETD();
	int ProcREF();
	int ProcDEREF();
	int ProcCOPYDEREF();
	int ProcSETDDEREF();
	int ProcWRITEDEREF();
	int ProcPUSHBEGIN();
	int ProcISNOTEND();
	int ProcNEXT();
	int ProcPUSHKEYVAL();
	int ProcFIND();
	int ProcFINDP();
	int ProcTHROW();
	int ProcTRY();
	int ProcTRYEXIT();
	int ProcPOPTO();

	PGLVMThread(PGLVM* vm);
	~PGLVMThread() {}
	PGLVM* GetVM() const {return m_mainVM;}
	int Entry(int paramCnt);
	int Resume();
	int Receive(PGLVMThread* from, int cnt);
	int GetState() const {return m_state;}
	void PushError(PGLVMError e, int addr);
	shared_ptr<PGLCompoundData> GetParameter(int i);
	size_t GetParameterCnt() const;
	void SetReturnCnt(size_t i);
	size_t GetReturnCnt() const {return m_retCnt;}
	void PushNull();
	void Push(const shared_ptr<PGLCompoundData>& data);
	void Pop(int n) {for(int i = 0; i < n; ++i) m_stack.pop_back();}
	int Throw() {return ProcTHROW();}
	int MakeArray(int n);
	int MakeDictionary(int n);
	string GetErrMsg() const {return m_err;}
	void SetUserData(void* ptr) {m_userPtr = ptr;}
	void* GetUserData() const {return m_userPtr;}
	void SetYieldCF(const shared_ptr<PGLCompoundData>& f) {m_yieldCF = f;}
};