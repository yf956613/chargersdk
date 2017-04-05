/**
* @file errorcode.c
* @brief
* @author rgw
* @version v1.0
* @date 2017-02-15
*/
#include "includes.h"
#include "errorcode.h"

//
//  һ��Ҫ��֤code�� **˳��** ��ͷ�ļ�����һ��
//
const uint8_t *strErrorCode[100] =
{
    "�޹���",
    "��ͣ��ⷢ������",
    "�������ٶȴ�������������",
    "�����ӵ������Դ�������������",
    "����״̬�������������",
    "��������������",

    "���� ���ͨ�Ź���",
    "���� ���CP����",
    "���� ���CC����",
    "���� ��ǹ״̬�������������",
    "���� B������ǹ��״̬�������������",
    "���� B������ǹ���޷���ֹ",
    "���� L�����¶ȼ�ⷢ������",
    "���� N�����¶ȼ�ⷢ������",
    "���� B�������¶ȼ���1��������",
    "���� B�������¶ȼ���2��������",
    "���� ��ʼ������",
    "���� ����������",

    "�ļ���д����",
    "��Ŀ���ļ�",
    "������������",
    "�������ݴ���",
    "��������",
    "����������",
    "������������żУ�����",
    "������������������",
    "����������֡����",
    "���������ڳ���",
    "����������DMA�������",
    "����ģ�鴮����żУ�����",
    "����ģ�鴮����������",
    "����ģ�鴮��֡����",
    "����ģ�鴮�ڳ���",
    "����ģ�鴮��DMA�������",
    "����ͨ�Ź���",
    "����ͨ�ų�ʱ",
    "�ڴ�������"
};

void ThrowErrorCode(uint32_t ulDevID, ErrorCode_t errcode, ErrorLevel_t errlevel)
{
    ErrorPackage_t package;

    package.ulDevID = ulDevID;
    package.code = errcode;
    package.level = errlevel;

    xQueueSend(xHandleQueueErrorPackage, (void *)&package, 0);
}

void ThrowFSCode (FRESULT rc)
{
    const char *str =
        "OK\0" "DISK_ERR\0" "INT_ERR\0" "NOT_READY\0" "NO_FILE\0" "NO_PATH\0"
        "INVALID_NAME\0" "DENIED\0" "EXIST\0" "INVALID_OBJECT\0" "WRITE_PROTECTED\0"
        "INVALID_DRIVE\0" "NOT_ENABLED\0" "NO_FILE_SYSTEM\0" "MKFS_ABORTED\0" "TIMEOUT\0"
        "LOCKED\0" "NOT_ENOUGH_CORE\0" "TOO_MANY_OPEN_FILES\0" "INVALID_PARAMETER\0";
    FRESULT i;
    if(rc != 0)
    {
        for (i = 0; i != rc && *str; i++)
        {
            while (*str++) ;
        }
        printf_safe("rc=%u FR_%s\n", (UINT)rc, str);
    }
}
