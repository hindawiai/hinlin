<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * xhci-debugfs.h - xHCI debugfs पूर्णांकerface
 *
 * Copyright (C) 2017 Intel Corporation
 *
 * Author: Lu Baolu <baolu.lu@linux.पूर्णांकel.com>
 */

#अगर_अघोषित __LINUX_XHCI_DEBUGFS_H
#घोषणा __LINUX_XHCI_DEBUGFS_H

#समावेश <linux/debugfs.h>

#घोषणा DEBUGFS_NAMELEN 32

#घोषणा REG_CAPLENGTH					0x00
#घोषणा REG_HCSPARAMS1					0x04
#घोषणा REG_HCSPARAMS2					0x08
#घोषणा REG_HCSPARAMS3					0x0c
#घोषणा REG_HCCPARAMS1					0x10
#घोषणा REG_DOORBELLOFF					0x14
#घोषणा REG_RUNTIMखातापूर्णF					0x18
#घोषणा REG_HCCPARAMS2					0x1c

#घोषणा	REG_USBCMD					0x00
#घोषणा REG_USBSTS					0x04
#घोषणा REG_PAGESIZE					0x08
#घोषणा REG_DNCTRL					0x14
#घोषणा REG_CRCR					0x18
#घोषणा REG_DCBAAP_LOW					0x30
#घोषणा REG_DCBAAP_HIGH					0x34
#घोषणा REG_CONFIG					0x38

#घोषणा REG_MFINDEX					0x00
#घोषणा REG_IR0_IMAN					0x20
#घोषणा REG_IR0_IMOD					0x24
#घोषणा REG_IR0_ERSTSZ					0x28
#घोषणा REG_IR0_ERSTBA_LOW				0x30
#घोषणा REG_IR0_ERSTBA_HIGH				0x34
#घोषणा REG_IR0_ERDP_LOW				0x38
#घोषणा REG_IR0_ERDP_HIGH				0x3c

#घोषणा REG_EXTCAP_USBLEGSUP				0x00
#घोषणा REG_EXTCAP_USBLEGCTLSTS				0x04

#घोषणा REG_EXTCAP_REVISION				0x00
#घोषणा REG_EXTCAP_NAME					0x04
#घोषणा REG_EXTCAP_PORTINFO				0x08
#घोषणा REG_EXTCAP_PORTTYPE				0x0c
#घोषणा REG_EXTCAP_MANTISSA1				0x10
#घोषणा REG_EXTCAP_MANTISSA2				0x14
#घोषणा REG_EXTCAP_MANTISSA3				0x18
#घोषणा REG_EXTCAP_MANTISSA4				0x1c
#घोषणा REG_EXTCAP_MANTISSA5				0x20
#घोषणा REG_EXTCAP_MANTISSA6				0x24

#घोषणा REG_EXTCAP_DBC_CAPABILITY			0x00
#घोषणा REG_EXTCAP_DBC_DOORBELL				0x04
#घोषणा REG_EXTCAP_DBC_ERSTSIZE				0x08
#घोषणा REG_EXTCAP_DBC_ERST_LOW				0x10
#घोषणा REG_EXTCAP_DBC_ERST_HIGH			0x14
#घोषणा REG_EXTCAP_DBC_ERDP_LOW				0x18
#घोषणा REG_EXTCAP_DBC_ERDP_HIGH			0x1c
#घोषणा REG_EXTCAP_DBC_CONTROL				0x20
#घोषणा REG_EXTCAP_DBC_STATUS				0x24
#घोषणा REG_EXTCAP_DBC_PORTSC				0x28
#घोषणा REG_EXTCAP_DBC_CONT_LOW				0x30
#घोषणा REG_EXTCAP_DBC_CONT_HIGH			0x34
#घोषणा REG_EXTCAP_DBC_DEVINFO1				0x38
#घोषणा REG_EXTCAP_DBC_DEVINFO2				0x3c

#घोषणा dump_रेजिस्टर(nm)				\
अणु							\
	.name	= __stringअगरy(nm),			\
	.offset	= REG_ ##nm,				\
पूर्ण

काष्ठा xhci_regset अणु
	अक्षर			name[DEBUGFS_NAMELEN];
	काष्ठा debugfs_regset32	regset;
	माप_प्रकार			nregs;
	काष्ठा list_head	list;
पूर्ण;

काष्ठा xhci_file_map अणु
	स्थिर अक्षर		*name;
	पूर्णांक			(*show)(काष्ठा seq_file *s, व्योम *unused);
पूर्ण;

काष्ठा xhci_ep_priv अणु
	अक्षर			name[DEBUGFS_NAMELEN];
	काष्ठा dentry		*root;
	काष्ठा xhci_stream_info *stream_info;
	काष्ठा xhci_ring	*show_ring;
	अचिन्हित पूर्णांक		stream_id;
पूर्ण;

काष्ठा xhci_slot_priv अणु
	अक्षर			name[DEBUGFS_NAMELEN];
	काष्ठा dentry		*root;
	काष्ठा xhci_ep_priv	*eps[31];
	काष्ठा xhci_virt_device	*dev;
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS
व्योम xhci_debugfs_init(काष्ठा xhci_hcd *xhci);
व्योम xhci_debugfs_निकास(काष्ठा xhci_hcd *xhci);
व्योम __init xhci_debugfs_create_root(व्योम);
व्योम __निकास xhci_debugfs_हटाओ_root(व्योम);
व्योम xhci_debugfs_create_slot(काष्ठा xhci_hcd *xhci, पूर्णांक slot_id);
व्योम xhci_debugfs_हटाओ_slot(काष्ठा xhci_hcd *xhci, पूर्णांक slot_id);
व्योम xhci_debugfs_create_endpoपूर्णांक(काष्ठा xhci_hcd *xhci,
				  काष्ठा xhci_virt_device *virt_dev,
				  पूर्णांक ep_index);
व्योम xhci_debugfs_हटाओ_endpoपूर्णांक(काष्ठा xhci_hcd *xhci,
				  काष्ठा xhci_virt_device *virt_dev,
				  पूर्णांक ep_index);
व्योम xhci_debugfs_create_stream_files(काष्ठा xhci_hcd *xhci,
				      काष्ठा xhci_virt_device *virt_dev,
				      पूर्णांक ep_index);
#अन्यथा
अटल अंतरभूत व्योम xhci_debugfs_init(काष्ठा xhci_hcd *xhci) अणु पूर्ण
अटल अंतरभूत व्योम xhci_debugfs_निकास(काष्ठा xhci_hcd *xhci) अणु पूर्ण
अटल अंतरभूत व्योम __init xhci_debugfs_create_root(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम __निकास xhci_debugfs_हटाओ_root(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम xhci_debugfs_create_slot(काष्ठा xhci_hcd *x, पूर्णांक s) अणु पूर्ण
अटल अंतरभूत व्योम xhci_debugfs_हटाओ_slot(काष्ठा xhci_hcd *x, पूर्णांक s) अणु पूर्ण
अटल अंतरभूत व्योम
xhci_debugfs_create_endpoपूर्णांक(काष्ठा xhci_hcd *xhci,
			     काष्ठा xhci_virt_device *virt_dev,
			     पूर्णांक ep_index) अणु पूर्ण
अटल अंतरभूत व्योम
xhci_debugfs_हटाओ_endpoपूर्णांक(काष्ठा xhci_hcd *xhci,
			     काष्ठा xhci_virt_device *virt_dev,
			     पूर्णांक ep_index) अणु पूर्ण
अटल अंतरभूत व्योम
xhci_debugfs_create_stream_files(काष्ठा xhci_hcd *xhci,
				 काष्ठा xhci_virt_device *virt_dev,
				 पूर्णांक ep_index) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

#पूर्ण_अगर /* __LINUX_XHCI_DEBUGFS_H */
