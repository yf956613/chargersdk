#ifndef __OBSERVER_H__
#define __OBSERVER_H__
#include <string.h>
#include "userlib_list.h"
//抽像通知者接口
typedef struct _Subject
{
    char *(*GetSubjectState)(void *pSubject);
    void (*SetSubjectState)(void *pSubject, char *pSubjectState);
    void (*Attach)(void *pSubject, void *pObserver);
    void (*Detach)(void *pSubject, void *pObserver);
    void (*Notify)(void *pSubject);
    void (*Delete)(void *pSubject);
}Subject_t;

//抽像观察者
typedef struct _Observer
{
    char *Name;
    Subject_t *pSub;
    void (*Update)(void *pObserver);
    void (*Delete)(void *pObserver);
}Observer_t;

Observer_t *ObserverCreate(char *Name, void *pSub, size_t Size);
Subject_t *SubjectCreate(size_t Size);
#endif
