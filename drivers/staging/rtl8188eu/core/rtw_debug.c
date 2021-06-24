<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTW_DEBUG_C_

#समावेश <rtw_debug.h>
#समावेश <usb_ops_linux.h>

पूर्णांक proc_get_drv_version(अक्षर *page, अक्षर **start,
			 off_t offset, पूर्णांक count,
			 पूर्णांक *eof, व्योम *data)
अणु
	पूर्णांक len = 0;

	len += scnम_लिखो(page + len, count - len, "%s\n", DRIVERVERSION);

	*eof = 1;
	वापस len;
पूर्ण

पूर्णांक proc_get_ग_लिखो_reg(अक्षर *page, अक्षर **start,
		       off_t offset, पूर्णांक count,
		       पूर्णांक *eof, व्योम *data)
अणु
	*eof = 1;
	वापस 0;
पूर्ण

पूर्णांक proc_set_ग_लिखो_reg(काष्ठा file *file, स्थिर अक्षर __user *buffer,
		       अचिन्हित दीर्घ count, व्योम *data)
अणु
	काष्ठा net_device *dev = data;
	काष्ठा adapter *padapter = netdev_priv(dev);
	अक्षर पंचांगp[32];
	u32 addr, val, len;

	अगर (count < 3) अणु
		DBG_88E("argument size is less than 3\n");
		वापस -EFAULT;
	पूर्ण

	अगर (buffer && !copy_from_user(पंचांगp, buffer, माप(पंचांगp))) अणु
		पूर्णांक num = माला_पूछो(पंचांगp, "%x %x %x", &addr, &val, &len);

		अगर (num !=  3) अणु
			DBG_88E("invalid write_reg parameter!\n");
			वापस count;
		पूर्ण
		चयन (len) अणु
		हाल 1:
			usb_ग_लिखो8(padapter, addr, (u8)val);
			अवरोध;
		हाल 2:
			usb_ग_लिखो16(padapter, addr, (u16)val);
			अवरोध;
		हाल 4:
			usb_ग_लिखो32(padapter, addr, val);
			अवरोध;
		शेष:
			DBG_88E("error write length =%d", len);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस count;
पूर्ण

अटल u32 proc_get_पढ़ो_addr = 0xeeeeeeee;
अटल u32 proc_get_पढ़ो_len = 0x4;

पूर्णांक proc_get_पढ़ो_reg(अक्षर *page, अक्षर **start,
		      off_t offset, पूर्णांक count,
		      पूर्णांक *eof, व्योम *data)
अणु
	काष्ठा net_device *dev = data;
	काष्ठा adapter *padapter = netdev_priv(dev);

	पूर्णांक len = 0;

	अगर (proc_get_पढ़ो_addr == 0xeeeeeeee) अणु
		*eof = 1;
		वापस len;
	पूर्ण

	चयन (proc_get_पढ़ो_len) अणु
	हाल 1:
		len += scnम_लिखो(page + len, count - len, "usb_read8(0x%x)=0x%x\n",
				 proc_get_पढ़ो_addr, usb_पढ़ो8(padapter, proc_get_पढ़ो_addr));
		अवरोध;
	हाल 2:
		len += scnम_लिखो(page + len, count - len, "usb_read16(0x%x)=0x%x\n",
				 proc_get_पढ़ो_addr, usb_पढ़ो16(padapter, proc_get_पढ़ो_addr));
		अवरोध;
	हाल 4:
		len += scnम_लिखो(page + len, count - len, "usb_read32(0x%x)=0x%x\n",
				 proc_get_पढ़ो_addr, usb_पढ़ो32(padapter, proc_get_पढ़ो_addr));
		अवरोध;
	शेष:
		len += scnम_लिखो(page + len, count - len, "error read length=%d\n",
				 proc_get_पढ़ो_len);
		अवरोध;
	पूर्ण

	*eof = 1;
	वापस len;
पूर्ण

पूर्णांक proc_set_पढ़ो_reg(काष्ठा file *file, स्थिर अक्षर __user *buffer,
		      अचिन्हित दीर्घ count, व्योम *data)
अणु
	अक्षर पंचांगp[16];
	u32 addr, len;

	अगर (count < 2) अणु
		DBG_88E("argument size is less than 2\n");
		वापस -EFAULT;
	पूर्ण

	अगर (buffer && !copy_from_user(पंचांगp, buffer, माप(पंचांगp))) अणु
		पूर्णांक num = माला_पूछो(पंचांगp, "%x %x", &addr, &len);

		अगर (num !=  2) अणु
			DBG_88E("invalid read_reg parameter!\n");
			वापस count;
		पूर्ण

		proc_get_पढ़ो_addr = addr;

		proc_get_पढ़ो_len = len;
	पूर्ण

	वापस count;
पूर्ण

पूर्णांक proc_get_adapter_state(अक्षर *page, अक्षर **start,
			   off_t offset, पूर्णांक count,
			   पूर्णांक *eof, व्योम *data)
अणु
	काष्ठा net_device *dev = data;
	काष्ठा adapter *padapter = netdev_priv(dev);
	पूर्णांक len = 0;

	len += scnम_लिखो(page + len, count - len, "bSurpriseRemoved=%d, bDriverStopped=%d\n",
			 padapter->bSurpriseRemoved,
			 padapter->bDriverStopped);

	*eof = 1;
	वापस len;
पूर्ण

पूर्णांक proc_get_best_channel(अक्षर *page, अक्षर **start,
			  off_t offset, पूर्णांक count,
			  पूर्णांक *eof, व्योम *data)
अणु
	काष्ठा net_device *dev = data;
	काष्ठा adapter *padapter = netdev_priv(dev);
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	पूर्णांक len = 0;
	u32 i, best_channel_24G = 1, index_24G = 0;

	क्रम (i = 0; pmlmeext->channel_set[i].ChannelNum != 0; i++) अणु
		अगर (pmlmeext->channel_set[i].ChannelNum == 1)
			index_24G = i;
	पूर्ण

	क्रम (i = 0; pmlmeext->channel_set[i].ChannelNum != 0; i++) अणु
		/*  2.4G */
		अगर (pmlmeext->channel_set[i].ChannelNum == 6) अणु
			अगर (pmlmeext->channel_set[i].rx_count < pmlmeext->channel_set[index_24G].rx_count) अणु
				index_24G = i;
				best_channel_24G = pmlmeext->channel_set[i].ChannelNum;
			पूर्ण
		पूर्ण

		/*  debug */
		len += scnम_लिखो(page + len, count - len, "The rx cnt of channel %3d = %d\n",
				 pmlmeext->channel_set[i].ChannelNum,
				 pmlmeext->channel_set[i].rx_count);
	पूर्ण

	len += scnम_लिखो(page + len, count - len, "best_channel_24G = %d\n", best_channel_24G);

	*eof = 1;
	वापस len;
पूर्ण
