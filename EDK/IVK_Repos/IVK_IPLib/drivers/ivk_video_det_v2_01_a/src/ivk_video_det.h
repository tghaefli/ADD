// ----------------------------------------------------------------
//      _____
//     /     \
//    /____   \____
//   / \===\   \==/
//  /___\===\___\/  AVNET
//       \======/
//        \====/    
// ----------------------------------------------------------------
//
// This design is the property of Avnet.  Publication of this
// design is not authorized without written consent from Avnet.
// 
// Please direct any questions to:  technical.support@avnet.com
//
// Disclaimer:
//    Avnet, Inc. makes no warranty for the use of this code or design.
//    This code is provided  "As Is". Avnet, Inc assumes no responsibility for
//    any errors, which may appear in this code, nor does it make a commitment
//    to update the information contained herein. Avnet, Inc specifically
//    disclaims any implied warranties of fitness for a particular purpose.
//                     Copyright(c) 2010 Avnet, Inc.
//                             All rights reserved.
//
// ----------------------------------------------------------------
//
// Create Date:         Feb 18, 2010
// Design Name:         IVK
// Module Name:         ivk_video_det.h
// Project Name:        IVK
// Target Devices:      Spartan-6
// Avnet Boards:        IVK
//
// Tool versions:       ISE 11.4
//
// Description:         Header
//
// Dependencies:        
//
// Revision:            Feb 18, 2010: 1.00 Initial Version
//
// ----------------------------------------------------------------

#ifndef __IVK_VIDEO_DET_H__
#define __IVK_VIDEO_DET_H__

/***************************** Include Files *******************************/

#include "xbasic_types.h"
#include "xstatus.h"
#include "xio.h"

/************************** Constant Definitions ***************************/


/**
 * User Logic Slave Space Offsets
 * -- SLV_REG0 : user logic slave module register 0
 * -- SLV_REG1 : user logic slave module register 1
 * -- SLV_REG2 : user logic slave module register 2
 * -- SLV_REG3 : user logic slave module register 3
 */
#define IVK_VIDEO_DET_USER_SLV_SPACE_OFFSET (0x00000000)
#define IVK_VIDEO_DET_SLV_REG0_OFFSET (IVK_VIDEO_DET_USER_SLV_SPACE_OFFSET + 0x00000000)
#define IVK_VIDEO_DET_SLV_REG1_OFFSET (IVK_VIDEO_DET_USER_SLV_SPACE_OFFSET + 0x00000004)
#define IVK_VIDEO_DET_SLV_REG2_OFFSET (IVK_VIDEO_DET_USER_SLV_SPACE_OFFSET + 0x00000008)
#define IVK_VIDEO_DET_SLV_REG3_OFFSET (IVK_VIDEO_DET_USER_SLV_SPACE_OFFSET + 0x0000000C)

/**
 * Software Reset Space Register Offsets
 * -- RST : software reset register
 */
#define IVK_VIDEO_DET_SOFT_RST_SPACE_OFFSET (0x00000100)
#define IVK_VIDEO_DET_RST_REG_OFFSET (IVK_VIDEO_DET_SOFT_RST_SPACE_OFFSET + 0x00000000)

/**
 * Software Reset Masks
 * -- SOFT_RESET : software reset
 */
#define SOFT_RESET (0x0000000A)

/**************************** Type Definitions *****************************/


/***************** Macros (Inline Functions) Definitions *******************/

/**
 *
 * Write a value to a IVK_VIDEO_DET register. A 32 bit write is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is written.
 *
 * @param   BaseAddress is the base address of the IVK_VIDEO_DET device.
 * @param   RegOffset is the register offset from the base to write to.
 * @param   Data is the data written to the register.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void IVK_VIDEO_DET_mWriteReg(Xuint32 BaseAddress, unsigned RegOffset, Xuint32 Data)
 *
 */
#define IVK_VIDEO_DET_mWriteReg(BaseAddress, RegOffset, Data) \
 	XIo_Out32((BaseAddress) + (RegOffset), (Xuint32)(Data))

/**
 *
 * Read a value from a IVK_VIDEO_DET register. A 32 bit read is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is read from the register. The most significant data
 * will be read as 0.
 *
 * @param   BaseAddress is the base address of the IVK_VIDEO_DET device.
 * @param   RegOffset is the register offset from the base to write to.
 *
 * @return  Data is the data from the register.
 *
 * @note
 * C-style signature:
 * 	Xuint32 IVK_VIDEO_DET_mReadReg(Xuint32 BaseAddress, unsigned RegOffset)
 *
 */
#define IVK_VIDEO_DET_mReadReg(BaseAddress, RegOffset) \
 	XIo_In32((BaseAddress) + (RegOffset))


/**
 *
 * Write/Read 32 bit value to/from IVK_VIDEO_DET user logic slave registers.
 *
 * @param   BaseAddress is the base address of the IVK_VIDEO_DET device.
 * @param   RegOffset is the offset from the slave register to write to or read from.
 * @param   Value is the data written to the register.
 *
 * @return  Data is the data from the user logic slave register.
 *
 * @note
 * C-style signature:
 * 	void IVK_VIDEO_DET_mWriteSlaveRegn(Xuint32 BaseAddress, unsigned RegOffset, Xuint32 Value)
 * 	Xuint32 IVK_VIDEO_DET_mReadSlaveRegn(Xuint32 BaseAddress, unsigned RegOffset)
 *
 */
#define IVK_VIDEO_DET_mWriteSlaveReg0(BaseAddress, RegOffset, Value) \
 	XIo_Out32((BaseAddress) + (IVK_VIDEO_DET_SLV_REG0_OFFSET) + (RegOffset), (Xuint32)(Value))
#define IVK_VIDEO_DET_mWriteSlaveReg1(BaseAddress, RegOffset, Value) \
 	XIo_Out32((BaseAddress) + (IVK_VIDEO_DET_SLV_REG1_OFFSET) + (RegOffset), (Xuint32)(Value))
#define IVK_VIDEO_DET_mWriteSlaveReg2(BaseAddress, RegOffset, Value) \
 	XIo_Out32((BaseAddress) + (IVK_VIDEO_DET_SLV_REG2_OFFSET) + (RegOffset), (Xuint32)(Value))
#define IVK_VIDEO_DET_mWriteSlaveReg3(BaseAddress, RegOffset, Value) \
 	XIo_Out32((BaseAddress) + (IVK_VIDEO_DET_SLV_REG3_OFFSET) + (RegOffset), (Xuint32)(Value))

#define IVK_VIDEO_DET_mReadSlaveReg0(BaseAddress, RegOffset) \
 	XIo_In32((BaseAddress) + (IVK_VIDEO_DET_SLV_REG0_OFFSET) + (RegOffset))
#define IVK_VIDEO_DET_mReadSlaveReg1(BaseAddress, RegOffset) \
 	XIo_In32((BaseAddress) + (IVK_VIDEO_DET_SLV_REG1_OFFSET) + (RegOffset))
#define IVK_VIDEO_DET_mReadSlaveReg2(BaseAddress, RegOffset) \
 	XIo_In32((BaseAddress) + (IVK_VIDEO_DET_SLV_REG2_OFFSET) + (RegOffset))
#define IVK_VIDEO_DET_mReadSlaveReg3(BaseAddress, RegOffset) \
 	XIo_In32((BaseAddress) + (IVK_VIDEO_DET_SLV_REG3_OFFSET) + (RegOffset))

/**
 *
 * Reset IVK_VIDEO_DET via software.
 *
 * @param   BaseAddress is the base address of the IVK_VIDEO_DET device.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void IVK_VIDEO_DET_mReset(Xuint32 BaseAddress)
 *
 */
#define IVK_VIDEO_DET_mReset(BaseAddress) \
 	XIo_Out32((BaseAddress)+(IVK_VIDEO_DET_RST_REG_OFFSET), SOFT_RESET)


/************************** Function Prototypes ****************************/

/**
 *
 * Read the detected video dimensions.
 *
 * @param   BaseAddress is the base address of the DE_GEN device.
 *
 * @param   pWidth  : pointer to response for video width (horizontal active region)
 *
 * @param   pHeight : pointer to response for video height (vertical active region)
 *
 * @return  None.
 *
 * @note
 *
 */
void read_IVK_VIDEO_DET_video_dimensions(Xuint32 BaseAddress, Xuint32 *pWidth, Xuint32 *pHeight );


#endif // __IVK_VIDEO_DET_H__
