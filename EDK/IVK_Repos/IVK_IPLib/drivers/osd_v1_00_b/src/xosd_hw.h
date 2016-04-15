/* $Id: */

/******************************************************************************
*
*       XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS"
*       AS A COURTESY TO YOU, SOLELY FOR USE IN DEVELOPING PROGRAMS AND
*       SOLUTIONS FOR XILINX DEVICES.  BY PROVIDING THIS DESIGN, CODE,
*       OR INFORMATION AS ONE POSSIBLE IMPLEMENTATION OF THIS FEATURE,
*       APPLICATION OR STANDARD, XILINX IS MAKING NO REPRESENTATION
*       THAT THIS IMPLEMENTATION IS FREE FROM ANY CLAIMS OF INFRINGEMENT,
*       AND YOU ARE RESPONSIBLE FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE
*       FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY DISCLAIMS ANY
*       WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE
*       IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR
*       REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF
*       INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*       FOR A PARTICULAR PURPOSE.
*
*       (c) Copyright 2008 Xilinx Inc.
*       All rights reserved.
*
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xosd_hw.h
*
* This header file contains identifiers and register-level driver functions (or
* macros) that can be used to access the Xilinx MVI Video On-Screen-Display
* (OSD) device.
*
* For more information about the operation of this device, see the hardware
* specification and documentation in the higher level driver xosd.h source
* code file.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00a xd   08/01/08 First release
* </pre>
*
******************************************************************************/

#ifndef XOSD_HW_H        /* prevent circular inclusions */
#define XOSD_HW_H        /* by using protection macros */

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/

#include "xio.h"

/************************** Constant Definitions *****************************/

/**
 * Register Offsets
 */
#define XOSD_CTL            0x000    /**< Control */
#define XOSD_SS             0x010    /**< Screen Size */
#define XOSD_BC0            0x014    /**< Background Color Channel 0 */
#define XOSD_BC1            0x018    /**< Background Color Channel 1 */
#define XOSD_BC2            0x01C    /**< Background Color Channel 2 */

#define XOSD_L0C            0x020    /**< Layer 0 Control */
#define XOSD_L0P            0x024    /**< Layer 0 Position */
#define XOSD_L0S            0x028    /**< Layer 0 Size */

#define XOSD_L1C            0x030    /**< Layer 1 Control */
#define XOSD_L1P            0x034    /**< Layer 1 Position */
#define XOSD_L1S            0x038    /**< Layer 1 Size */

#define XOSD_L2C            0x040    /**< Layer 2 Control */
#define XOSD_L2P            0x044    /**< Layer 2 Position */
#define XOSD_L2S            0x048    /**< Layer 2 Size */

#define XOSD_L3C            0x050    /**< Layer 3 Control */
#define XOSD_L3P            0x054    /**< Layer 3 Position */
#define XOSD_L3S            0x058    /**< Layer 3 Size */

#define XOSD_L4C            0x060    /**< Layer 4 Control */
#define XOSD_L4P            0x064    /**< Layer 4 Position */
#define XOSD_L4S            0x068    /**< Layer 4 Size */

#define XOSD_L5C            0x070    /**< Layer 5 Control */
#define XOSD_L5P            0x074    /**< Layer 5 Position */
#define XOSD_L5S            0x078    /**< Layer 5 Size */

#define XOSD_L6C            0x080    /**< Layer 6 Control */
#define XOSD_L6P            0x084    /**< Layer 6 Position */
#define XOSD_L6S            0x088    /**< Layer 6 Size */

#define XOSD_L7C            0x090    /**< Layer 7 Control */
#define XOSD_L7P            0x094    /**< Layer 7 Position */
#define XOSD_L7S            0x098    /**< Layer 7 Size */

#define XOSD_GCWBA          0x0A0    /**< GPU Write Bank Address */
#define XOSD_GCABA          0x0A4    /**< GPU Active Bank Address */
#define XOSD_GCD            0x0A8    /**< GPU Data */

#define XOSD_RST            0x100    /**< Software Reset */

#define XOSD_GIER           0x21C    /**< Global Interrupt Enable Register */
#define XOSD_ISR            0x220    /**< Interrupt Status Register */
#define XOSD_IER            0x228    /**< Interrupt Enable Register */

/**
 * Memory footprint of layers
 */
#define XOSD_LAYER_SIZE		0x10
#define XOSD_LXC            0x00    /**< Layer Control */
#define XOSD_LXP            0x04    /**< Layer Position */
#define XOSD_LXS            0x08    /**< Layer Size */

/**
 * Graphics Controller Bank related constants
 */
#define XOSD_GC_BANK_NUM	2		/**< The number of Banks in each Graphics
									  *  controller  */

/**
 * OSD Control Register bit definition
 */
#define XOSD_CTL_VBP_MASK    0x00000020 /**< Vertical Blank Polarity */
#define XOSD_CTL_HBP_MASK    0x00000010 /**< Horizontal Blank Polarity */
#define XOSD_CTL_RUE_MASK    0x00000004 /**< OSD Register Update Enable */
#define XOSD_CTL_EN_MASK     0x00000001 /**< OSD Enable */

/**
 * OSD Screen Size Register bit definition
 */
#define XOSD_SS_YSIZE_MASK   0x0FFF0000 /**< Vertical Height of OSD Output */
#define XOSD_SS_YSIZE_SHIFT  16         /**< Bit shift of XOSD_SS_YSIZE_MASK */
#define XOSD_SS_XSIZE_MASK   0x00000FFF /**< Horizontal Width of OSD Output */

/**
 * OSD Background Color Channel 0
 */
#define XOSD_BC0_YG_MASK     0x000003FF /**< Y (luma) or Green */

/**
 * OSD Background Color Channel 1
 */
#define XOSD_BC1_UCBB_MASK   0x000003FF /**< U (Cb) or Blue */

/**
 * OSD Background Color Channel 2
 */
#define XOSD_BC2_VCRR_MASK   0x000003FF /**< V(Cr) or Red */

/**
 * Maximum number of the layers
 */
#define XOSD_MAX_NUM_OF_LAYERS  8          /**< The max number of layers */

/**
 * OSD Layer Control (Layer 0 through (XOSD_MAX_NUM_OF_LAYERS - 1))
 */
#define XOSD_LXC_ALPHA_MASK     0x00FF0000 /**< Global Alpha Value */
#define XOSD_LXC_ALPHA_SHIFT    16         /**< Bit shift number of Global
                                             *  Alpha Value */
#define XOSD_LXC_PRIORITY_MASK  0x00000700 /**< Layer Priority */
#define XOSD_LXC_PRIORITY_SHIFT 8          /**< Bit shift number of Layer
                                             *  Priority */
#define XOSD_LXC_GALPHAEN_MASK  0x00000002 /**< Global Alpha Enable */
#define XOSD_LXC_EN_MASK        0x00000001 /**< Layer Enable */

/**
 * OSD Layer Position (Layer 0 through (XOSD_MAX_NUM_OF_LAYERS - 1))
 */
#define XOSD_LXP_YSTART_MASK    0x0FFF0000 /**< Vertical start line of origin
                                             *  of layer */
#define XOSD_LXP_YSTART_SHIFT   16         /**< Bit shift of vertical start
                                             *  line of origin of layer */
#define XOSD_LXP_XSTART_MASK    0x00000FFF /**< Horizontal start pixel of
                                             *  origin of layer */

/**
 * OSD Layer Size (Layer 0 through (XOSD_MAX_NUM_OF_LAYERS - 1))
 */
#define XOSD_LXS_YSIZE_MASK    0x0FFF0000 /**< Vertical size of layer */
#define XOSD_LXS_YSIZE_SHIFT   16         /**< Bit shift number of vertical
                                            *  size of layer */
#define XOSD_LXS_XSIZE_MASK    0x00000FFF /**< Horizontal size of layer */

/**
 * OSD Graphics Controller Write Bank Address
 */
#define XOSD_GCWBA_GCNUM_MASK  0x00000700 /**< Graphics Controller Number */
#define XOSD_GCWBA_GCNUM_SHIFT 8          /**< Bit shift of Graphics Controller
                                            *  Number */
#define XOSD_GCWBA_BANK_MASK   0x00000007 /**< Controls which bank to write GPU
											*  instructions and Color LUT data
											*  into. */
#define XOSD_GCWBA_INS0		   0x00000000 /** Instruction RAM 0 */
#define XOSD_GCWBA_INS1		   0x00000001 /** Instruction RAM 1 */
#define XOSD_GCWBA_COL0		   0x00000002 /** Color LUT RAM 0 */
#define XOSD_GCWBA_COL1		   0x00000003 /** Color LUT RAM 1 */
#define XOSD_GCWBA_TXT0		   0x00000004 /** Text RAM 0 */
#define XOSD_GCWBA_TXT1		   0x00000005 /** Text RAM 1 */
#define XOSD_GCWBA_CHR0        0x00000006 /** Character Set RAM 0 */
#define XOSD_GCWBA_CHR1		   0x00000007 /** Character Set RAM 1 */

/**
 * OSD Graphics Controller Active Bank Address
 */
#define XOSD_GCABA_CHR_MASK    0xFF000000 /**< Set the active Character Bank */
#define XOSD_GCABA_CHR_SHIFT   24         /**< Bit shift of active Character
                                            *  Bank */
#define XOSD_GCABA_TXT_MASK    0x00FF0000 /**< Set the active Text Bank */
#define XOSD_GCABA_TXT_SHIFT   16         /**< Bit shift of active Text Bank */
#define XOSD_GCABA_COL_MASK    0x0000FF00 /**< Set the active Color Table
                                            *  Bank */
#define XOSD_GCABA_COL_SHIFT   8          /**< Bit shift of active Color Table
                                            *  Bank */
#define XOSD_GCABA_INS_MASK    0x000000FF /**< Set the active instruction Bank
                                            */

/**
 * OSD Software Reset
 */
#define XOSD_RST_RESET		  0x0000000A /**< Software Reset */

/**
 * Global Interrupt Enable Register bit definition
 */
#define XOSD_GIER_GIE_MASK	  0x80000000 /**< Global interrupt enable */

/**
 * Interrupt Status/Enable Register bit definition
 */
#define XOSD_IXR_GAO_MASK	  0xFF000000 /**< Graphics Controller Instruction
                                           *  Overflow */
#define XOSD_IXR_GIE_MASK	  0x00FF0000 /**< Graphics Controller Instruction
                                           *  Error */
#define XOSD_IXR_OOE_MASK	  0x00001000 /**< OSD Output Overflow Error */
#define XOSD_IXR_IUE_MASK	  0x00000FF0 /**< OSD Input Underflow Error */
#define XOSD_IXR_VBIE_MASK	  0x00000008 /**< Vertical Blank Interval End */
#define XOSD_IXR_VBIS_MASK	  0x00000004 /**< Vertical Blank Interval Start */
#define XOSD_IXR_FE_MASK	  0x00000002 /**< OSD did not complete processing
                                           *  frame before next Vblank */
#define XOSD_IXR_FD_MASK	  0x00000001 /**< OSD completed processing Frame */

#define XOSD_IXR_ALLIERR_MASK (XOSD_IXR_GAO_MASK | \
                               XOSD_IXR_GIE_MASK | \
                               XOSD_IXR_OOE_MASK | \
                               XOSD_IXR_IUE_MASK | \
                               XOSD_IXR_FE_MASK) /**< Mask for all error
                                                   *  interrupts */

#define XOSD_IXR_ALLINTR_MASK  (XOSD_IXR_VBIE_MASK | \
                                XOSD_IXR_VBIS_MASK | \
                                XOSD_IXR_FD_MASK | \
                                XOSD_IXR_ALLIERR_MASK) /**< Mask for all
                                                         *  interrupts */

/**
 * Layer Types
 */
#define XOSD_LAYER_TYPE_DISABLE 0			/**< Layer is disabled    */
#define XOSD_LAYER_TYPE_GPU	    1			/**< Layer's type is GPU  */
#define XOSD_LAYER_TYPE_VFBC    2			/**< Layer's type is VFBC */

/**
 * Supported Instruction numbers given an instruction memory size
 */
#define XOSD_INS_MEM_SIZE_TO_NUM 1      /**< Conversion to the number of
                                          *  instructions from the
                                          *  instruction memory size */

/**
 * GC Instruction word offset definition
 */
#define XOSD_INS0		  	  0			/**< Instruction word 0 offset */
#define XOSD_INS1			  1			/**< Instruction word 1 offset */
#define XOSD_INS2			  2			/**< Instruction word 2 offset */
#define XOSD_INS3			  3			/**< Instruction word 3 offset */
#define XOSD_INS_SIZE		  4			/**< Size of an instruction in words */

/**
 * GC Instruction word 0 definition
 */
#define XOSD_INS0_OPCODE_MASK  0xF0000000	/**< Operation Code (OpCode) */
#define XOSD_INS0_OPCODE_SHIFT 28			/**< Bit shift number of OpCode */

#define XOSD_INS0_GCNUM_MASK  0x07000000	/**< Graphics controller number
                                              *  (GC#) */
#define XOSD_INS0_GCNUM_SHIFT 24			/**< Bit shift number of GC# */

#define XOSD_INS0_XEND_MASK   0x00FFF000	/**< Horizontal end pixel of the
                                              *  object */
#define XOSD_INS0_XEND_SHIFT  12			/**< Bit shift number of Horizontal
                                              *  end pixel of the object */
#define XOSD_INS0_XSTART_MASK 0x00000FFF	/**< Horizontal start pixel of the
                                              *  Object */

/**
 * GC Instruction word 1 definition
 */
#define XOSD_INS1_TXTINDEX_MASK 0x0000000F	/**< String Index */

/**
 * GC Instruction word 2 definition
 */
#define XOSD_INS2_OBJSIZE_MASK  0xFF000000	/**< Object Size */
#define XOSD_INS2_OBJSIZE_SHIFT 24			/**< Bit shift number of Object
                                              *  Size */
#define XOSD_INS2_YEND_MASK     0x00FFF000	/**< Vertical end line of the
                                              *  object */
#define XOSD_INS2_YEND_SHIFT    12			/**< Bit shift number of Vertical
											  *  end line of the object */
#define XOSD_INS2_YSTART_MASK   0x00000FFF	/**< Vertical start line of the
                                              *  Object */

/**
 * GC Instruction word 3 definition
 */
#define XOSD_INS3_COL_MASK    0x0000000F	/**< Color Index for Box/Text */

/**
 * GC Instruction Operation Code definition (used in Instruction word 0)
 */
#define XOSD_INS_OPCODE_END	   0x0			/**< End of instruction list */
#define XOSD_INS_OPCODE_NOP	   0x8			/**< NOP */
#define XOSD_INS_OPCODE_BOX	   0xA			/**< Box */
#define XOSD_INS_OPCODE_LINE   0xC			/**< Line */
#define XOSD_INS_OPCODE_TXT    0xE			/**< Text */
#define XOSD_INS_OPCODE_BOXTXT 0xF			/**< Box Text */

/**
 * GC color size
 */
#define XOSD_COLOR_ENTRY_SIZE	4	/**< Size of each color entry in bytes */

/**
 * GC font unit size
 */
#define XOSD_FONT_BIT_TO_BYTE	8	/**< Ratio to convert font size to byte */

/**
 * Layer priority
 */
#define XOSD_LAYER_PRIORITY_0		0		/**< Priority 0 --- Lowest */
#define XOSD_LAYER_PRIORITY_1		1		/**< Priority 1 */
#define XOSD_LAYER_PRIORITY_2		2		/**< Priority 2 */
#define XOSD_LAYER_PRIORITY_3		3		/**< Priority 3 */
#define XOSD_LAYER_PRIORITY_4		4		/**< Priority 4 */
#define XOSD_LAYER_PRIORITY_5		5		/**< Priority 5 */
#define XOSD_LAYER_PRIORITY_6		6		/**< Priority 6 */
#define XOSD_LAYER_PRIORITY_7		7		/**< Priority 7 --- Highest */

/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/

#define XOSD_In32          XIo_In32
#define XOSD_Out32         XIo_Out32

/*****************************************************************************/
/**
*
* Read the given register.
*
* @param    BaseAddress is the base address of the device
* @param    RegOffset is the register offset to be read
*
* @return   The 32-bit value of the register
*
* @note
* C-style signature:
*    u32 XOSD_ReadReg(u32 BaseAddress, u32 RegOffset)
*
******************************************************************************/
#define XOSD_ReadReg(BaseAddress, RegOffset) \
            XOSD_In32((BaseAddress) + (RegOffset))

/*****************************************************************************/
/**
*
* Write the given register.
*
* @param    BaseAddress is the base address of the device
* @param    RegOffset is the register offset to be written
* @param    Data is the 32-bit value to write to the register
*
* @return   None.
*
* @note
* C-style signature:
*    void XOSD_WriteReg(u32 BaseAddress, u32 RegOffset, u32 Data)
*
******************************************************************************/
#define XOSD_WriteReg(BaseAddress, RegOffset, Data) \
            XOSD_Out32((BaseAddress) + (RegOffset), (Data))

/************************** Function Prototypes ******************************/

#ifdef __cplusplus
}
#endif

#endif /* end of protection macro */
