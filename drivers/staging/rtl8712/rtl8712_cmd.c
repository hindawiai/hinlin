<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 * rtl8712_cmd.c
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 * Linux device driver क्रम RTL8192SU
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>.
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/

#घोषणा _RTL8712_CMD_C_

#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/module.h>
#समावेश <linux/kref.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/atomic.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/rtnetlink.h>

#समावेश "osdep_service.h"
#समावेश "drv_types.h"
#समावेश "recv_osdep.h"
#समावेश "mlme_osdep.h"
#समावेश "rtl871x_ioctl_set.h"

अटल व्योम check_hw_pbc(काष्ठा _adapter *padapter)
अणु
	u8	पंचांगp1byte;

	r8712_ग_लिखो8(padapter, MAC_PINMUX_CTRL, (GPIOMUX_EN | GPIOSEL_GPIO));
	पंचांगp1byte = r8712_पढ़ो8(padapter, GPIO_IO_SEL);
	पंचांगp1byte &= ~(HAL_8192S_HW_GPIO_WPS_BIT);
	r8712_ग_लिखो8(padapter, GPIO_IO_SEL, पंचांगp1byte);
	पंचांगp1byte = r8712_पढ़ो8(padapter, GPIO_CTRL);
	अगर (पंचांगp1byte == 0xff)
		वापस;
	अगर (पंचांगp1byte & HAL_8192S_HW_GPIO_WPS_BIT) अणु
		/* Here we only set bPbcPressed to true
		 * After trigger PBC, the variable will be set to false
		 */
		DBG_8712("CheckPbcGPIO - PBC is pressed !!!!\n");
		/* 0 is the शेष value and it means the application monitors
		 * the HW PBC करोesn't provide its pid to driver.
		 */
		अगर (padapter->pid == 0)
			वापस;
		समाप्त_pid(find_vpid(padapter->pid), SIGUSR1, 1);
	पूर्ण
पूर्ण

/* query rx phy status from fw.
 * Adhoc mode: beacon.
 * Infraकाष्ठाure mode: beacon , data.
 */
अटल व्योम query_fw_rx_phy_status(काष्ठा _adapter *padapter)
अणु
	u32 val32 = 0;
	पूर्णांक pollingcnts = 50;

	अगर (check_fwstate(&padapter->mlmepriv, _FW_LINKED)) अणु
		r8712_ग_लिखो32(padapter, IOCMD_CTRL_REG, 0xf4000001);
		msleep(100);
		/* Wait FW complete IO Cmd */
		जबतक ((r8712_पढ़ो32(padapter, IOCMD_CTRL_REG)) &&
		       (pollingcnts > 0)) अणु
			pollingcnts--;
			msleep(20);
		पूर्ण
		अगर (pollingcnts != 0)
			val32 = r8712_पढ़ो32(padapter, IOCMD_DATA_REG);
		अन्यथा /* समय out */
			val32 = 0;
		val32 >>= 4;
		padapter->recvpriv.fw_rssi =
			 (u8)r8712_संकेत_scale_mapping(val32);
	पूर्ण
पूर्ण

/* check mlme, hw, phy, or dynamic algorithm status. */
अटल व्योम StatusWatchकरोgCallback(काष्ठा _adapter *padapter)
अणु
	check_hw_pbc(padapter);
	query_fw_rx_phy_status(padapter);
पूर्ण

अटल व्योम r871x_पूर्णांकernal_cmd_hdl(काष्ठा _adapter *padapter, u8 *pbuf)
अणु
	काष्ठा drvपूर्णांक_cmd_parm *pdrvcmd;

	अगर (!pbuf)
		वापस;
	pdrvcmd = (काष्ठा drvपूर्णांक_cmd_parm *)pbuf;
	चयन (pdrvcmd->i_cid) अणु
	हाल WDG_WK_CID:
		StatusWatchकरोgCallback(padapter);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	kमुक्त(pdrvcmd->pbuf);
पूर्ण

अटल u8 पढ़ो_macreg_hdl(काष्ठा _adapter *padapter, u8 *pbuf)
अणु
	व्योम (*pcmd_callback)(काष्ठा _adapter *dev, काष्ठा cmd_obj	*pcmd);
	काष्ठा cmd_obj *pcmd  = (काष्ठा cmd_obj *)pbuf;

	/*  invoke cmd->callback function */
	pcmd_callback = cmd_callback[pcmd->cmdcode].callback;
	अगर (!pcmd_callback)
		r8712_मुक्त_cmd_obj(pcmd);
	अन्यथा
		pcmd_callback(padapter, pcmd);
	वापस H2C_SUCCESS;
पूर्ण

अटल u8 ग_लिखो_macreg_hdl(काष्ठा _adapter *padapter, u8 *pbuf)
अणु
	व्योम (*pcmd_callback)(काष्ठा _adapter *dev, काष्ठा cmd_obj	*pcmd);
	काष्ठा cmd_obj *pcmd  = (काष्ठा cmd_obj *)pbuf;

	/*  invoke cmd->callback function */
	pcmd_callback = cmd_callback[pcmd->cmdcode].callback;
	अगर (!pcmd_callback)
		r8712_मुक्त_cmd_obj(pcmd);
	अन्यथा
		pcmd_callback(padapter, pcmd);
	वापस H2C_SUCCESS;
पूर्ण

अटल u8 पढ़ो_bbreg_hdl(काष्ठा _adapter *padapter, u8 *pbuf)
अणु
	काष्ठा cmd_obj *pcmd  = (काष्ठा cmd_obj *)pbuf;

	r8712_मुक्त_cmd_obj(pcmd);
	वापस H2C_SUCCESS;
पूर्ण

अटल u8 ग_लिखो_bbreg_hdl(काष्ठा _adapter *padapter, u8 *pbuf)
अणु
	व्योम (*pcmd_callback)(काष्ठा _adapter *dev, काष्ठा cmd_obj *pcmd);
	काष्ठा cmd_obj *pcmd  = (काष्ठा cmd_obj *)pbuf;

	pcmd_callback = cmd_callback[pcmd->cmdcode].callback;
	अगर (!pcmd_callback)
		r8712_मुक्त_cmd_obj(pcmd);
	अन्यथा
		pcmd_callback(padapter, pcmd);
	वापस H2C_SUCCESS;
पूर्ण

अटल u8 पढ़ो_rfreg_hdl(काष्ठा _adapter *padapter, u8 *pbuf)
अणु
	u32 val;
	व्योम (*pcmd_callback)(काष्ठा _adapter *dev, काष्ठा cmd_obj *pcmd);
	काष्ठा cmd_obj *pcmd  = (काष्ठा cmd_obj *)pbuf;

	अगर (pcmd->rsp && pcmd->rspsz > 0)
		स_नकल(pcmd->rsp, (u8 *)&val, pcmd->rspsz);
	pcmd_callback = cmd_callback[pcmd->cmdcode].callback;
	अगर (!pcmd_callback)
		r8712_मुक्त_cmd_obj(pcmd);
	अन्यथा
		pcmd_callback(padapter, pcmd);
	वापस H2C_SUCCESS;
पूर्ण

अटल u8 ग_लिखो_rfreg_hdl(काष्ठा _adapter *padapter, u8 *pbuf)
अणु
	व्योम (*pcmd_callback)(काष्ठा _adapter *dev, काष्ठा cmd_obj *pcmd);
	काष्ठा cmd_obj *pcmd  = (काष्ठा cmd_obj *)pbuf;

	pcmd_callback = cmd_callback[pcmd->cmdcode].callback;
	अगर (!pcmd_callback)
		r8712_मुक्त_cmd_obj(pcmd);
	अन्यथा
		pcmd_callback(padapter, pcmd);
	वापस H2C_SUCCESS;
पूर्ण

अटल u8 sys_suspend_hdl(काष्ठा _adapter *padapter, u8 *pbuf)
अणु
	काष्ठा cmd_obj *pcmd  = (काष्ठा cmd_obj *)pbuf;

	r8712_मुक्त_cmd_obj(pcmd);
	वापस H2C_SUCCESS;
पूर्ण

अटल काष्ठा cmd_obj *cmd_hdl_filter(काष्ठा _adapter *padapter,
				      काष्ठा cmd_obj *pcmd)
अणु
	काष्ठा cmd_obj *pcmd_r;

	अगर (!pcmd)
		वापस pcmd;
	pcmd_r = शून्य;

	चयन (pcmd->cmdcode) अणु
	हाल GEN_CMD_CODE(_Read_MACREG):
		पढ़ो_macreg_hdl(padapter, (u8 *)pcmd);
		pcmd_r = pcmd;
		अवरोध;
	हाल GEN_CMD_CODE(_Write_MACREG):
		ग_लिखो_macreg_hdl(padapter, (u8 *)pcmd);
		pcmd_r = pcmd;
		अवरोध;
	हाल GEN_CMD_CODE(_Read_BBREG):
		पढ़ो_bbreg_hdl(padapter, (u8 *)pcmd);
		अवरोध;
	हाल GEN_CMD_CODE(_Write_BBREG):
		ग_लिखो_bbreg_hdl(padapter, (u8 *)pcmd);
		अवरोध;
	हाल GEN_CMD_CODE(_Read_RFREG):
		पढ़ो_rfreg_hdl(padapter, (u8 *)pcmd);
		अवरोध;
	हाल GEN_CMD_CODE(_Write_RFREG):
		ग_लिखो_rfreg_hdl(padapter, (u8 *)pcmd);
		अवरोध;
	हाल GEN_CMD_CODE(_SetUsbSuspend):
		sys_suspend_hdl(padapter, (u8 *)pcmd);
		अवरोध;
	हाल GEN_CMD_CODE(_JoinBss):
		r8712_joinbss_reset(padapter);
		/* Beक्रमe set JoinBss_CMD to FW, driver must ensure FW is in
		 * PS_MODE_ACTIVE. Directly ग_लिखो rpwm to radio on and assign
		 * new pwr_mode to Driver, instead of use workitem to change
		 * state.
		 */
		अगर (padapter->pwrctrlpriv.pwr_mode > PS_MODE_ACTIVE) अणु
			padapter->pwrctrlpriv.pwr_mode = PS_MODE_ACTIVE;
			mutex_lock(&padapter->pwrctrlpriv.mutex_lock);
			r8712_set_rpwm(padapter, PS_STATE_S4);
			mutex_unlock(&padapter->pwrctrlpriv.mutex_lock);
		पूर्ण
		pcmd_r = pcmd;
		अवरोध;
	हाल _DRV_INT_CMD_:
		r871x_पूर्णांकernal_cmd_hdl(padapter, pcmd->parmbuf);
		r8712_मुक्त_cmd_obj(pcmd);
		pcmd_r = शून्य;
		अवरोध;
	शेष:
		pcmd_r = pcmd;
		अवरोध;
	पूर्ण
	वापस pcmd_r; /* अगर वापसing pcmd_r == शून्य, pcmd must be मुक्त. */
पूर्ण

u8 r8712_fw_cmd(काष्ठा _adapter *pAdapter, u32 cmd)
अणु
	पूर्णांक pollingcnts = 50;

	r8712_ग_लिखो32(pAdapter, IOCMD_CTRL_REG, cmd);
	msleep(100);
	जबतक ((r8712_पढ़ो32(pAdapter, IOCMD_CTRL_REG != 0)) &&
	       (pollingcnts > 0)) अणु
		pollingcnts--;
		msleep(20);
	पूर्ण
	अगर (pollingcnts == 0)
		वापस false;
	वापस true;
पूर्ण

व्योम r8712_fw_cmd_data(काष्ठा _adapter *pAdapter, u32 *value, u8 flag)
अणु
	अगर (flag == 0)	/* set */
		r8712_ग_लिखो32(pAdapter, IOCMD_DATA_REG, *value);
	अन्यथा		/* query */
		*value = r8712_पढ़ो32(pAdapter, IOCMD_DATA_REG);
पूर्ण

पूर्णांक r8712_cmd_thपढ़ो(व्योम *context)
अणु
	काष्ठा cmd_obj *pcmd;
	अचिन्हित पूर्णांक cmdsz, wr_sz;
	__le32 *pcmdbuf;
	काष्ठा tx_desc *pdesc;
	व्योम (*pcmd_callback)(काष्ठा _adapter *dev, काष्ठा cmd_obj *pcmd);
	काष्ठा _adapter *padapter = context;
	काष्ठा	cmd_priv *pcmdpriv = &padapter->cmdpriv;
	काष्ठा completion *cmd_queue_comp =
		&pcmdpriv->cmd_queue_comp;
	काष्ठा mutex *pwctrl_lock = &padapter->pwrctrlpriv.mutex_lock;

	allow_संकेत(संक_इति);
	जबतक (1) अणु
		अगर (रुको_क्रम_completion_पूर्णांकerruptible(cmd_queue_comp))
			अवरोध;
		अगर (padapter->driver_stopped || padapter->surprise_हटाओd)
			अवरोध;
		अगर (r8712_रेजिस्टर_cmd_alive(padapter))
			जारी;
_next:
		pcmd = r8712_dequeue_cmd(&pcmdpriv->cmd_queue);
		अगर (!(pcmd)) अणु
			r8712_unरेजिस्टर_cmd_alive(padapter);
			जारी;
		पूर्ण
		pcmdbuf = (__le32 *)pcmdpriv->cmd_buf;
		pdesc = (काष्ठा tx_desc *)pcmdbuf;
		स_रखो(pdesc, 0, TXDESC_SIZE);
		pcmd = cmd_hdl_filter(padapter, pcmd);
		अगर (pcmd) अणु /* अगर pcmd != शून्य, cmd will be handled by f/w */
			काष्ठा dvobj_priv *pdvobj = &padapter->dvobjpriv;
			u8 blnPending = 0;
			u16 cmdcode = pcmd->cmdcode;

			pcmdpriv->cmd_issued_cnt++;
			cmdsz = round_up(pcmd->cmdsz, 8);
			wr_sz = TXDESC_SIZE + 8 + cmdsz;
			pdesc->txdw0 |= cpu_to_le32((wr_sz - TXDESC_SIZE) &
						     0x0000ffff);
			अगर (pdvobj->ishighspeed) अणु
				अगर ((wr_sz % 512) == 0)
					blnPending = 1;
			पूर्ण अन्यथा अणु
				अगर ((wr_sz % 64) == 0)
					blnPending = 1;
			पूर्ण
			अगर (blnPending) अणु /* 32 bytes क्रम TX Desc - 8 offset */
				pdesc->txdw0 |= cpu_to_le32(((TXDESC_SIZE +
						OFFSET_SZ + 8) << OFFSET_SHT) &
						0x00ff0000);
			पूर्ण अन्यथा अणु
				pdesc->txdw0 |= cpu_to_le32(((TXDESC_SIZE +
							      OFFSET_SZ) <<
							      OFFSET_SHT) &
							      0x00ff0000);
			पूर्ण
			pdesc->txdw0 |= cpu_to_le32(OWN | FSG | LSG);
			pdesc->txdw1 |= cpu_to_le32((0x13 << QSEL_SHT) &
						    0x00001f00);
			pcmdbuf += (TXDESC_SIZE >> 2);
			*pcmdbuf = cpu_to_le32((cmdsz & 0x0000ffff) |
					       (pcmd->cmdcode << 16) |
					       (pcmdpriv->cmd_seq << 24));
			pcmdbuf += 2; /* 8 bytes alignment */
			स_नकल((u8 *)pcmdbuf, pcmd->parmbuf, pcmd->cmdsz);
			अगर (blnPending)
				wr_sz += 8;   /* Append 8 bytes */
			r8712_ग_लिखो_mem(padapter, RTL8712_DMA_H2CCMD, wr_sz,
					(u8 *)pdesc);
			pcmdpriv->cmd_seq++;
			अगर (cmdcode == GEN_CMD_CODE(_CreateBss)) अणु
				pcmd->res = H2C_SUCCESS;
				pcmd_callback = cmd_callback[cmdcode].callback;
				अगर (pcmd_callback)
					pcmd_callback(padapter, pcmd);
				जारी;
			पूर्ण
			अगर (cmdcode == GEN_CMD_CODE(_SetPwrMode)) अणु
				अगर (padapter->pwrctrlpriv.bSleep) अणु
					mutex_lock(pwctrl_lock);
					r8712_set_rpwm(padapter, PS_STATE_S2);
					mutex_unlock(pwctrl_lock);
				पूर्ण
			पूर्ण
			r8712_मुक्त_cmd_obj(pcmd);
			अगर (list_empty(&pcmdpriv->cmd_queue.queue)) अणु
				r8712_unरेजिस्टर_cmd_alive(padapter);
				जारी;
			पूर्ण अन्यथा अणु
				जाओ _next;
			पूर्ण
		पूर्ण अन्यथा अणु
			जाओ _next;
		पूर्ण
		flush_संकेतs_thपढ़ो();
	पूर्ण
	/* मुक्त all cmd_obj resources */
	करो अणु
		pcmd = r8712_dequeue_cmd(&pcmdpriv->cmd_queue);
		अगर (!pcmd)
			अवरोध;
		r8712_मुक्त_cmd_obj(pcmd);
	पूर्ण जबतक (1);
	complete(&pcmdpriv->terminate_cmdthपढ़ो_comp);
	thपढ़ो_निकास();
पूर्ण

व्योम r8712_event_handle(काष्ठा _adapter *padapter, __le32 *peventbuf)
अणु
	u8 evt_code, evt_seq;
	u16 evt_sz;
	व्योम (*event_callback)(काष्ठा _adapter *dev, u8 *pbuf);
	काष्ठा	evt_priv *pevt_priv = &padapter->evtpriv;

	अगर (!peventbuf)
		जाओ _पात_event_;
	evt_sz = (u16)(le32_to_cpu(*peventbuf) & 0xffff);
	evt_seq = (u8)((le32_to_cpu(*peventbuf) >> 24) & 0x7f);
	evt_code = (u8)((le32_to_cpu(*peventbuf) >> 16) & 0xff);
	/* checking event sequence... */
	अगर ((evt_seq & 0x7f) != pevt_priv->event_seq) अणु
		pevt_priv->event_seq = ((evt_seq + 1) & 0x7f);
		जाओ _पात_event_;
	पूर्ण
	/* checking अगर event code is valid */
	अगर (evt_code >= MAX_C2HEVT) अणु
		pevt_priv->event_seq = ((evt_seq + 1) & 0x7f);
		जाओ _पात_event_;
	पूर्ण अन्यथा अगर ((evt_code == GEN_EVT_CODE(_Survey)) &&
		   (evt_sz > माप(काष्ठा wlan_bssid_ex))) अणु
		pevt_priv->event_seq = ((evt_seq + 1) & 0x7f);
		जाओ _पात_event_;
	पूर्ण
	/* checking अगर event size match the event parm size */
	अगर ((wlanevents[evt_code].parmsize) &&
	    (wlanevents[evt_code].parmsize != evt_sz)) अणु
		pevt_priv->event_seq = ((evt_seq + 1) & 0x7f);
		जाओ _पात_event_;
	पूर्ण अन्यथा अगर ((evt_sz == 0) && (evt_code != GEN_EVT_CODE(_WPS_PBC))) अणु
		pevt_priv->event_seq = ((evt_seq + 1) & 0x7f);
		जाओ _पात_event_;
	पूर्ण
	pevt_priv->event_seq++;	/* update evt_seq */
	अगर (pevt_priv->event_seq > 127)
		pevt_priv->event_seq = 0;
	/* move to event content, 8 bytes alignment */
	peventbuf = peventbuf + 2;
	event_callback = wlanevents[evt_code].event_callback;
	अगर (event_callback)
		event_callback(padapter, (u8 *)peventbuf);
	pevt_priv->evt_करोne_cnt++;
_पात_event_:
	वापस;
पूर्ण
