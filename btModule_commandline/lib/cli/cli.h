/** 
 **************************************************************
 * @file btModule_commandline/lib/cli/cli.cpp
 * @author Cameron Stroud - 44344968
 * @date 14062020
 * @brief CLI Task header file
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * 
 *************************************************************** 
 */

#ifndef __CLI_H
#define __CLI_H

/* Function prototypes -------------------------------------------------------*/
void cli_init( void );
void serial_print(const char *payload, ...);

#endif // __CLI_H