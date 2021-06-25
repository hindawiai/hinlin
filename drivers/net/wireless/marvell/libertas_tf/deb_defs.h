<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/**
  * This header file contains global स्थिरant/क्रमागत definitions,
  * global variable declaration.
  */
#अगर_अघोषित _LBS_DEB_DEFS_H_
#घोषणा _LBS_DEB_DEFS_H_

#अगर_अघोषित DRV_NAME
#घोषणा DRV_NAME "libertas_tf"
#पूर्ण_अगर

#समावेश <linux/spinlock.h>

#अगर_घोषित CONFIG_LIBERTAS_THINFIRM_DEBUG
#घोषणा DEBUG
#घोषणा PROC_DEBUG
#पूर्ण_अगर

#घोषणा LBTF_DEB_ENTER	0x00000001
#घोषणा LBTF_DEB_LEAVE	0x00000002
#घोषणा LBTF_DEB_MAIN	0x00000004
#घोषणा LBTF_DEB_NET	0x00000008
#घोषणा LBTF_DEB_MESH	0x00000010
#घोषणा LBTF_DEB_WEXT	0x00000020
#घोषणा LBTF_DEB_IOCTL	0x00000040
#घोषणा LBTF_DEB_SCAN	0x00000080
#घोषणा LBTF_DEB_ASSOC	0x00000100
#घोषणा LBTF_DEB_JOIN	0x00000200
#घोषणा LBTF_DEB_11D	0x00000400
#घोषणा LBTF_DEB_DEBUGFS	0x00000800
#घोषणा LBTF_DEB_ETHTOOL	0x00001000
#घोषणा LBTF_DEB_HOST	0x00002000
#घोषणा LBTF_DEB_CMD	0x00004000
#घोषणा LBTF_DEB_RX	0x00008000
#घोषणा LBTF_DEB_TX	0x00010000
#घोषणा LBTF_DEB_USB	0x00020000
#घोषणा LBTF_DEB_CS	0x00040000
#घोषणा LBTF_DEB_FW	0x00080000
#घोषणा LBTF_DEB_THREAD	0x00100000
#घोषणा LBTF_DEB_HEX	0x00200000
#घोषणा LBTF_DEB_SDIO	0x00400000
#घोषणा LBTF_DEB_MACOPS	0x00800000

बाह्य अचिन्हित पूर्णांक lbtf_debug;


#अगर_घोषित DEBUG
#घोषणा LBTF_DEB_LL(grp, grpnam, fmt, args...) \
करो अणु अगर ((lbtf_debug & (grp)) == (grp)) \
  prपूर्णांकk(KERN_DEBUG DRV_NAME grpnam ": " fmt, ## args); पूर्ण जबतक (0)
#अन्यथा
#घोषणा LBTF_DEB_LL(grp, grpnam, fmt, args...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा lbtf_deb_enter(grp) \
  LBTF_DEB_LL(grp | LBTF_DEB_ENTER, " enter", "%s()\n", __func__);
#घोषणा lbtf_deb_enter_args(grp, fmt, args...) \
  LBTF_DEB_LL(grp | LBTF_DEB_ENTER, " enter", "%s(" fmt ")\n", __func__, ## args);
#घोषणा lbtf_deb_leave(grp) \
  LBTF_DEB_LL(grp | LBTF_DEB_LEAVE, " leave", "%s()\n", __func__);
#घोषणा lbtf_deb_leave_args(grp, fmt, args...) \
  LBTF_DEB_LL(grp | LBTF_DEB_LEAVE, " leave", "%s(), " fmt "\n", \
  __func__, ##args);
#घोषणा lbtf_deb_मुख्य(fmt, args...)      LBTF_DEB_LL(LBTF_DEB_MAIN, " main", fmt, ##args)
#घोषणा lbtf_deb_net(fmt, args...)       LBTF_DEB_LL(LBTF_DEB_NET, " net", fmt, ##args)
#घोषणा lbtf_deb_mesh(fmt, args...)      LBTF_DEB_LL(LBTF_DEB_MESH, " mesh", fmt, ##args)
#घोषणा lbtf_deb_wext(fmt, args...)      LBTF_DEB_LL(LBTF_DEB_WEXT, " wext", fmt, ##args)
#घोषणा lbtf_deb_ioctl(fmt, args...)     LBTF_DEB_LL(LBTF_DEB_IOCTL, " ioctl", fmt, ##args)
#घोषणा lbtf_deb_scan(fmt, args...)      LBTF_DEB_LL(LBTF_DEB_SCAN, " scan", fmt, ##args)
#घोषणा lbtf_deb_assoc(fmt, args...)     LBTF_DEB_LL(LBTF_DEB_ASSOC, " assoc", fmt, ##args)
#घोषणा lbtf_deb_join(fmt, args...)      LBTF_DEB_LL(LBTF_DEB_JOIN, " join", fmt, ##args)
#घोषणा lbtf_deb_11d(fmt, args...)       LBTF_DEB_LL(LBTF_DEB_11D, " 11d", fmt, ##args)
#घोषणा lbtf_deb_debugfs(fmt, args...)   LBTF_DEB_LL(LBTF_DEB_DEBUGFS, " debugfs", fmt, ##args)
#घोषणा lbtf_deb_ethtool(fmt, args...)   LBTF_DEB_LL(LBTF_DEB_ETHTOOL, " ethtool", fmt, ##args)
#घोषणा lbtf_deb_host(fmt, args...)      LBTF_DEB_LL(LBTF_DEB_HOST, " host", fmt, ##args)
#घोषणा lbtf_deb_cmd(fmt, args...)       LBTF_DEB_LL(LBTF_DEB_CMD, " cmd", fmt, ##args)
#घोषणा lbtf_deb_rx(fmt, args...)        LBTF_DEB_LL(LBTF_DEB_RX, " rx", fmt, ##args)
#घोषणा lbtf_deb_tx(fmt, args...)        LBTF_DEB_LL(LBTF_DEB_TX, " tx", fmt, ##args)
#घोषणा lbtf_deb_fw(fmt, args...)        LBTF_DEB_LL(LBTF_DEB_FW, " fw", fmt, ##args)
#घोषणा lbtf_deb_usb(fmt, args...)       LBTF_DEB_LL(LBTF_DEB_USB, " usb", fmt, ##args)
#घोषणा lbtf_deb_usbd(dev, fmt, args...) LBTF_DEB_LL(LBTF_DEB_USB, " usbd", "%s:" fmt, dev_name(dev), ##args)
#घोषणा lbtf_deb_cs(fmt, args...)        LBTF_DEB_LL(LBTF_DEB_CS, " cs", fmt, ##args)
#घोषणा lbtf_deb_thपढ़ो(fmt, args...)    LBTF_DEB_LL(LBTF_DEB_THREAD, " thread", fmt, ##args)
#घोषणा lbtf_deb_sdio(fmt, args...)      LBTF_DEB_LL(LBTF_DEB_SDIO, " thread", fmt, ##args)
#घोषणा lbtf_deb_macops(fmt, args...)      LBTF_DEB_LL(LBTF_DEB_MACOPS, " thread", fmt, ##args)

#अगर_घोषित DEBUG
अटल अंतरभूत व्योम lbtf_deb_hex(अचिन्हित पूर्णांक grp, स्थिर अक्षर *prompt, u8 *buf, पूर्णांक len)
अणु
	अक्षर newprompt[32];

	अगर (len &&
	    (lbtf_debug & LBTF_DEB_HEX) &&
	    (lbtf_debug & grp))	अणु
		snम_लिखो(newprompt, माप(newprompt), DRV_NAME " %s: ", prompt);
		prपूर्णांक_hex_dump_bytes(prompt, DUMP_PREFIX_NONE, buf, len);
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा lbtf_deb_hex(grp, prompt, buf, len)	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#पूर्ण_अगर
