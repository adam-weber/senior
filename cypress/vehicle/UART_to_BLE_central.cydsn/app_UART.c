/*******************************************************************************
* File Name: app_UART.c
*
* Description:
*  Common BLE application code for client devices.
*
*******************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "app_UART.h"
#include "project.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
const uint8 flash_storage[16] = {0};

void StoreInFlash(uint8 *newData, uint8 length)
{
    /* make sure the BLE stack is not in low-power mode */
    CyBle_ExitLPM();

    /* repeat flash write attempt until success */


        /* write segment of configuration structure from RAM into flash */
        CYBLE_API_RESULT_T result = CyBle_StoreAppData(
            newData,                    /* uint8 pointer to source data */
            (uint8_t *)&flash_storage,  /* uint8 pointer to const destination */
            length,                     /* number of bytes to write */
            0);                         /* don't force write, but loop will keep retrying */

}
/*******************************************************************************
* Function Name: HandleUartRxTraffic
********************************************************************************
*
* Summary:
*  This function takes data from received notfications and pushes it to the 
*  UART TX buffer. 
*
* Parameters:
*  CYBLE_GATTC_HANDLE_VALUE_NTF_PARAM_T * - the notification parameter as  
*                                           recieved by the BLE stack
*
* Return:
*   None.
*
*******************************************************************************/
void HandleUartRxTraffic(CYBLE_GATTC_HANDLE_VALUE_NTF_PARAM_T *uartRxDataNotification)
{
    if(uartRxDataNotification->handleValPair.attrHandle == txCharHandle)
    {
        UART_SpiUartPutArray(uartRxDataNotification->handleValPair.value.val, \
            (uint32) uartRxDataNotification->handleValPair.value.len);
    }
   
}


/*******************************************************************************
* Function Name: HandleUartTxTraffic
********************************************************************************
*
* Summary:
*  This function takes data from UART RX buffer and pushes it to the server 
*  as Write Without Response command.
*
* Parameters:
*  None.
*
* Return:
*   None.
*
*******************************************************************************/
uint8 WriteArray[16] = { (uint8) 0x52, (uint8) 0x65, (uint8) 0x64, (uint8) 0x42, (uint8) 0x65, (uint8) 0x61,(uint8) 0x72,(uint8) 0x2c,(uint8) 0x30,(uint8) 0x30, (uint8) 0x30, (uint8) 0x30, (uint8) 0x30,(uint8) 0x30, (uint8) 0x30, (uint8) 0x25};   	
uint8	WriteArray2[16];	
char	WriteArray3[16];
uint8	ReadArray[7];	
uint8   Temp[15];


void HandleUartTxTraffic(void)
{
    uint8 WriteArray[16] = { (uint8) 0x52, (uint8) 0x65, (uint8) 0x64, (uint8) 0x42, (uint8) 0x65, (uint8) 0x61,(uint8) 0x72,(uint8) 0x2c};//(uint8) 0x30,(uint8) 0x30, (uint8) 0x30, (uint8) 0x30, (uint8) 0x30,(uint8) 0x30, (uint8) 0x30, (uint8) 0x25};
    uint8   index;
    uint8   uartTxData[mtuSize];
    uint16  uartTxDataLength;	
    CYBLE_API_RESULT_T              bleApiResult;
    CYBLE_GATTC_WRITE_CMD_REQ_T     uartTxDataWriteCmd;
    //	Fill Array with values
    extern int count;
    int result = CyBle_GetRssi();
    
    long long int   m_z = 0;
    long long int   m_w = 0;
 //   long long int result = 0;
    char test[16];
    uint8 CountString[8];
    char temp[8];
    int count2 = 5;
     //   sprintf(temp,"%d", count2);
    int k;
        for(k=0; k<=8; k++){
        char test2 = temp[k];
        if (test2 == '0'){
        CountString[k] = (uint8) 0x30;
        } else if (test2 == '1'){
        CountString[k] = (uint8) 0x31;   
        } else if (test2 == '2'){
        CountString[k] = (uint8) 0x32;   
        }else if (test2 == '3'){
        CountString[k] = (uint8) 0x33;   
        }else if (test2 == '4'){
        CountString[k] = (uint8) 0x34;   
        }else if (test2 == '5'){
        CountString[k] = (uint8) 0x35;   
        }else if (test2 == '6'){
        CountString[k] = (uint8) 0x36;   
        }else if (test2 == '7'){
        CountString[k] = (uint8) 0x37;   
        }else if (test2 == '8'){
        CountString[k] = (uint8) 0x38;   
        }else if (test2 == '9'){
        CountString[k] = (uint8) 0x39;   
        } else
        CountString[k] = (uint8) 0x40;
        }
    char resultString[7]; //= {1,2,3,4,5,6,7};

    StoreInFlash(CountString,16);
    //memcpy(WriteArray2, flash_storage,16);
    //if (WriteArray2[0] == (uint8) 0x35){
      //     WriteArray3[0] = 11;
   // }
  //  m_z = (36969 * (int)WriteArray3[0-(strlen(WriteArray3)-1)]) * ((m_z) + 65535) + (m_z >> 16);
   // m_w = (18000 * (int)WriteArray3[0-(strlen(WriteArray3)-1)]) * ((m_w) + 65535) + (m_w >> 16);
   // result = ((m_z << 16) + m_w) % 7123489;
 //   WriteArray[8] = (uint8) 0x33;
    sprintf(resultString,"%d", result);

      for(k=0; k<=8; k++){
        char test = resultString[k];
        if (test == '0'){
        WriteArray[(8+k)] = (uint8) 0x30;
        } else if (test == '1'){
        WriteArray[(8+k)] = (uint8) 0x31;   
        } else if (test == '2'){
        WriteArray[(8+k)] = (uint8) 0x32;   
        }else if (test == '3'){
        WriteArray[(8+k)] = (uint8) 0x33;   
        }else if (test == '4'){
        WriteArray[(8+k)] = (uint8) 0x34;   
        }else if (test == '5'){
        WriteArray[(8+k)] = (uint8) 0x35;   
        }else if (test == '6'){
        WriteArray[(8+k)] = (uint8) 0x36;   
        }else if (test == '7'){
        WriteArray[(8+k)] = (uint8) 0x37;   
        }else if (test == '8'){
        WriteArray[(8+k)] = (uint8) 0x38;   
        }else if (test == '9'){
        WriteArray[(8+k)] = (uint8) 0x39;   
        } else
        WriteArray[(8+k)] = (uint8) 0x40;
    }
    
//    StoreInFlash(WriteArray, 16);

//    memcpy(flash_storage,WriteArray2, 16);


    uartTxDataWriteCmd.value.len  = 20;
    uartTxDataWriteCmd.attrHandle = rxCharHandle;
    uartTxDataWriteCmd.value.val  = WriteArray;          

    CyBle_GattcWriteWithoutResponse(cyBle_connHandle, &uartTxDataWriteCmd);
    CyBle_ProcessEvents();


   
}




/*****************************************************************************************
* Function Name: DisableUartRxInt
******************************************************************************************
*
* Summary:
*  This function disables the UART RX interrupt.
*
* Parameters:
*   None.
*
* Return:
*   None.
*
*****************************************************************************************/
void DisableUartRxInt(void)
{
    UART_INTR_RX_MASK_REG &= ~UART_RX_INTR_MASK;  
}

/*****************************************************************************************
* Function Name: EnableUartRxInt
******************************************************************************************
*
* Summary:
*  This function enables the UART RX interrupt.
*
* Parameters:
*   None.
*
* Return:
*   None.
*
*****************************************************************************************/
void EnableUartRxInt(void)
{
    UART_INTR_RX_MASK_REG |= UART_RX_INTR_MASK;  
}

/* [] END OF FILE */
