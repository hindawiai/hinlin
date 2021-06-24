<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
/*++
Copyright (c) Realtek Semiconductor Corp. All rights reserved.

Module Name:
	HalPwrSeqCmd.c

Abstract:
	Implement HW Power sequence configuration CMD handling routine क्रम Realtek devices.

Major Change History:
	When       Who               What
	---------- ---------------   -------------------------------
	2011-10-26 Lucas            Modअगरy to be compatible with SD4-CE driver.
	2011-07-07 Roger            Create.

--*/
#समावेश <drv_types.h>
#समावेश <rtw_debug.h>
#समावेश <HalPwrSeqCmd.h>


/*  */
/*  Description: */
/*  This routine deal with the Power Configuration CMDs parsing क्रम RTL8723/RTL8188E Series IC. */
/*  */
/*  Assumption: */
/*  We should follow specअगरic क्रमmat which was released from HW SD. */
/*  */
/*  2011.07.07, added by Roger. */
/*  */
u8 HalPwrSeqCmdParsing(
	काष्ठा adapter *padapter,
	u8 CutVersion,
	u8 FabVersion,
	u8 InterfaceType,
	काष्ठा wlan_pwr_cfg PwrSeqCmd[]
)
अणु
	काष्ठा wlan_pwr_cfg PwrCfgCmd;
	u8 bPollingBit = false;
	u32 AryIdx = 0;
	u8 value = 0;
	u32 offset = 0;
	u32 pollingCount = 0; /*  polling स्वतःload करोne. */
	u32 maxPollingCnt = 5000;

	करो अणु
		PwrCfgCmd = PwrSeqCmd[AryIdx];

		/* 2 Only Handle the command whose FAB, CUT, and Interface are matched */
		अगर (
			(GET_PWR_CFG_FAB_MASK(PwrCfgCmd) & FabVersion) &&
			(GET_PWR_CFG_CUT_MASK(PwrCfgCmd) & CutVersion) &&
			(GET_PWR_CFG_INTF_MASK(PwrCfgCmd) & InterfaceType)
		) अणु
			चयन (GET_PWR_CFG_CMD(PwrCfgCmd)) अणु
			हाल PWR_CMD_READ:
				अवरोध;

			हाल PWR_CMD_WRITE:
				offset = GET_PWR_CFG_OFFSET(PwrCfgCmd);

				/*  */
				/*  <Roger_Notes> We should deal with पूर्णांकerface specअगरic address mapping क्रम some पूर्णांकerfaces, e.g., SDIO पूर्णांकerface */
				/*  2011.07.07. */
				/*  */
				अगर (GET_PWR_CFG_BASE(PwrCfgCmd) == PWR_BASEADDR_SDIO) अणु
					/*  Read Back SDIO Local value */
					value = SdioLocalCmd52Read1Byte(padapter, offset);

					value &= ~(GET_PWR_CFG_MASK(PwrCfgCmd));
					value |= (
						GET_PWR_CFG_VALUE(PwrCfgCmd) &
						GET_PWR_CFG_MASK(PwrCfgCmd)
					);

					/*  Write Back SDIO Local value */
					SdioLocalCmd52Write1Byte(padapter, offset, value);
				पूर्ण अन्यथा अणु
					/*  Read the value from प्रणाली रेजिस्टर */
					value = rtw_पढ़ो8(padapter, offset);

					value &= (~(GET_PWR_CFG_MASK(PwrCfgCmd)));
					value |= (
						GET_PWR_CFG_VALUE(PwrCfgCmd)
						&GET_PWR_CFG_MASK(PwrCfgCmd)
					);

					/*  Write the value back to प्रणाली रेजिस्टर */
					rtw_ग_लिखो8(padapter, offset, value);
				पूर्ण
				अवरोध;

			हाल PWR_CMD_POLLING:

				bPollingBit = false;
				offset = GET_PWR_CFG_OFFSET(PwrCfgCmd);
				करो अणु
					अगर (GET_PWR_CFG_BASE(PwrCfgCmd) == PWR_BASEADDR_SDIO)
						value = SdioLocalCmd52Read1Byte(padapter, offset);
					अन्यथा
						value = rtw_पढ़ो8(padapter, offset);

					value = value&GET_PWR_CFG_MASK(PwrCfgCmd);
					अगर (
						value == (GET_PWR_CFG_VALUE(PwrCfgCmd) &
						GET_PWR_CFG_MASK(PwrCfgCmd))
					)
						bPollingBit = true;
					अन्यथा
						udelay(10);

					अगर (pollingCount++ > maxPollingCnt)
						वापस false;

				पूर्ण जबतक (!bPollingBit);

				अवरोध;

			हाल PWR_CMD_DELAY:
				अगर (GET_PWR_CFG_VALUE(PwrCfgCmd) == PWRSEQ_DELAY_US)
					udelay(GET_PWR_CFG_OFFSET(PwrCfgCmd));
				अन्यथा
					udelay(GET_PWR_CFG_OFFSET(PwrCfgCmd)*1000);
				अवरोध;

			हाल PWR_CMD_END:
				/*  When this command is parsed, end the process */
				वापस true;

			शेष:
				अवरोध;
			पूर्ण
		पूर्ण

		AryIdx++;/* Add Array Index */
	पूर्ण जबतक (1);

	वापस true;
पूर्ण
