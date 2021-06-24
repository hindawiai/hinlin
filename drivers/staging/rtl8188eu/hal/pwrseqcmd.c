<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#समावेश <pwrseqcmd.h>
#समावेश <usb_ops_linux.h>

/* This routine deals with the Power Configuration CMDs parsing
 * क्रम RTL8723/RTL8188E Series IC.
 */
u8 rtl88eu_pwrseqcmdparsing(काष्ठा adapter *padapter, u8 cut_vers,
			    काष्ठा wl_pwr_cfg pwrseqcmd[])
अणु
	काष्ठा wl_pwr_cfg pwrcfgcmd;
	u8 poll_bit = false;
	u32 aryidx = 0;
	u8 value = 0;
	u32 offset = 0;
	u32 poll_count = 0; /*  polling स्वतःload करोne. */
	u32 max_poll_count = 5000;

	करो अणु
		pwrcfgcmd = pwrseqcmd[aryidx];

		RT_TRACE(_module_hal_init_c_, _drv_info_,
			 ("%s: offset(%#x) cut_msk(%#x)"
			  " cmd(%#x)"
			  "msk(%#x) value(%#x)\n",
			  __func__,
			  GET_PWR_CFG_OFFSET(pwrcfgcmd),
			  GET_PWR_CFG_CUT_MASK(pwrcfgcmd),
			  GET_PWR_CFG_CMD(pwrcfgcmd),
			  GET_PWR_CFG_MASK(pwrcfgcmd),
			  GET_PWR_CFG_VALUE(pwrcfgcmd)));

		/* Only Handle the command whose CUT is matched */
		अगर (GET_PWR_CFG_CUT_MASK(pwrcfgcmd) & cut_vers) अणु
			चयन (GET_PWR_CFG_CMD(pwrcfgcmd)) अणु
			हाल PWR_CMD_READ:
				RT_TRACE(_module_hal_init_c_, _drv_info_,
					 ("%s: PWR_CMD_READ\n", __func__));
				अवरोध;
			हाल PWR_CMD_WRITE:
				RT_TRACE(_module_hal_init_c_, _drv_info_,
					 ("%s: PWR_CMD_WRITE\n", __func__));
				offset = GET_PWR_CFG_OFFSET(pwrcfgcmd);

				/*  Read the value from प्रणाली रेजिस्टर */
				value = usb_पढ़ो8(padapter, offset);

				value &= ~(GET_PWR_CFG_MASK(pwrcfgcmd));
				value |= (GET_PWR_CFG_VALUE(pwrcfgcmd) &
					  GET_PWR_CFG_MASK(pwrcfgcmd));

				/*  Write the value back to प्रणाली रेजिस्टर */
				usb_ग_लिखो8(padapter, offset, value);
				अवरोध;
			हाल PWR_CMD_POLLING:
				RT_TRACE(_module_hal_init_c_, _drv_info_,
					 ("%s: PWR_CMD_POLLING\n", __func__));

				poll_bit = false;
				offset = GET_PWR_CFG_OFFSET(pwrcfgcmd);
				करो अणु
					value = usb_पढ़ो8(padapter, offset);
					value &= GET_PWR_CFG_MASK(pwrcfgcmd);

					अगर (value == (GET_PWR_CFG_VALUE(pwrcfgcmd) &
						      GET_PWR_CFG_MASK(pwrcfgcmd)))
						poll_bit = true;
					अन्यथा
						udelay(10);

					अगर (poll_count++ > max_poll_count) अणु
						DBG_88E("Fail to polling Offset[%#x]\n", offset);
						वापस false;
					पूर्ण
				पूर्ण जबतक (!poll_bit);
				अवरोध;
			हाल PWR_CMD_DELAY:
				RT_TRACE(_module_hal_init_c_, _drv_info_,
					 ("%s: PWR_CMD_DELAY\n", __func__));
				अगर (GET_PWR_CFG_VALUE(pwrcfgcmd) == PWRSEQ_DELAY_US)
					udelay(GET_PWR_CFG_OFFSET(pwrcfgcmd));
				अन्यथा
					udelay(GET_PWR_CFG_OFFSET(pwrcfgcmd) * 1000);
				अवरोध;
			हाल PWR_CMD_END:
				/* When this command is parsed, end the process */
				RT_TRACE(_module_hal_init_c_, _drv_info_,
					 ("%s: PWR_CMD_END\n", __func__));
				वापस true;
			शेष:
				RT_TRACE(_module_hal_init_c_, _drv_err_,
					 ("%s: Unknown CMD!!\n", __func__));
				अवरोध;
			पूर्ण
		पूर्ण

		aryidx++;/* Add Array Index */
	पूर्ण जबतक (1);
	वापस true;
पूर्ण
