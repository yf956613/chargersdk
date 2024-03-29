#include "bsp.h"
#include "taskcreate.h"
#include "cli_main.h"
#include "ring_buffer.h"
#include "evse_config.h"

ring_buffer_s *term_rb;

void retarget_init(void)
{
    term_rb = ring_uint8_init(1024);
}
int printf_safe(const char *fmt, ...)
{
    char str[256] = { 0 };
    va_list va;

    va_start(va, fmt);
    vsnprintf(str, sizeof(str) - 1, fmt, va);
    va_end(va);
    
    uart_write_fast(cli_huart, (uint8_t *)str, strlen(str));

#if EVSE_USING_GUI
    ring_buffer_put(term_rb, str, strlen(str));
#endif
    return 0;
}

int printf(const char *fmt, ...) __attribute__((alias("printf_safe")));

#if 0
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

#pragma import(__use_no_semihosting_swi)

struct __FILE
{
    int handle;
};
FILE __stdout;
FILE __stdin;
FILE __stderr;
#ifdef __GNUC__
int _write (int fd, char *ptr, int len)
{
    int i = 0;
    uint8_t ch;
    while (*ptr && (i < len))
    {
        myputc(*ptr);
        i++;
        ptr++;
    }
    return i;
}
#else
/**
  * @brief  重定向标准库函数printf对应的基础库函数.
  * @param  None
  * @retval None
  */
int fputc(int ch, FILE *f)
{
    /*
    由于Windows中终端换行是"\r\n", 而tinysh中全部用的是'\n'结尾,无法完成换行,
    在此进行兼容
    */

    myputc(ch);

    return ch;
}

int fgetc(FILE *f)
{
    int ch;
    HAL_UART_Receive(&CLI_UARTx_Handler, (uint8_t *)&ch, 1, 1000);
    return ch;
}

int ferror(FILE *f)
{
    return EOF;
}
#endif



void _ttywrch(int ch)
{
    char tempch = ch;
    HAL_UART_Transmit(&CLI_UARTx_Handler, (uint8_t *)&tempch, 1, 0xFFFF);
}

void _sys_exit(int x)
{
    x = x;
}

#endif
