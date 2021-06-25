<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * QLogic iSCSI Offload Driver
 * Copyright (c) 2016 Cavium Inc.
 */

#अगर_अघोषित _QEDI_DBG_H_
#घोषणा _QEDI_DBG_H_

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/compiler.h>
#समावेश <linux/माला.स>
#समावेश <linux/version.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_transport_iscsi.h>
#समावेश <linux/fs.h>

#घोषणा __PREVENT_QED_HSI__
#समावेश <linux/qed/common_hsi.h>
#समावेश <linux/qed/qed_अगर.h>

बाह्य uपूर्णांक qedi_dbg_log;

/* Debug prपूर्णांक level definitions */
#घोषणा QEDI_LOG_DEFAULT	0x1		/* Set शेष logging mask */
#घोषणा QEDI_LOG_INFO		0x2		/* Inक्रमmational logs,
						 * MAC address, WWPN, WWNN
						 */
#घोषणा QEDI_LOG_DISC		0x4		/* Init, discovery, rport */
#घोषणा QEDI_LOG_LL2		0x8		/* LL2, VLAN logs */
#घोषणा QEDI_LOG_CONN		0x10		/* Connection setup, cleanup */
#घोषणा QEDI_LOG_EVT		0x20		/* Events, link, mtu */
#घोषणा QEDI_LOG_TIMER		0x40		/* Timer events */
#घोषणा QEDI_LOG_MP_REQ		0x80		/* Middle Path (MP) logs */
#घोषणा QEDI_LOG_SCSI_TM	0x100		/* SCSI Aborts, Task Mgmt */
#घोषणा QEDI_LOG_UNSOL		0x200		/* unsolicited event logs */
#घोषणा QEDI_LOG_IO		0x400		/* scsi cmd, completion */
#घोषणा QEDI_LOG_MQ		0x800		/* Multi Queue logs */
#घोषणा QEDI_LOG_BSG		0x1000		/* BSG logs */
#घोषणा QEDI_LOG_DEBUGFS	0x2000		/* debugFS logs */
#घोषणा QEDI_LOG_LPORT		0x4000		/* lport logs */
#घोषणा QEDI_LOG_ELS		0x8000		/* ELS logs */
#घोषणा QEDI_LOG_NPIV		0x10000		/* NPIV logs */
#घोषणा QEDI_LOG_SESS		0x20000		/* Connection setup, cleanup */
#घोषणा QEDI_LOG_UIO		0x40000		/* iSCSI UIO logs */
#घोषणा QEDI_LOG_TID		0x80000         /* FW TID context acquire,
						 * मुक्त
						 */
#घोषणा QEDI_TRACK_TID		0x100000        /* Track TID state. To be
						 * enabled only at module load
						 * and not run-समय.
						 */
#घोषणा QEDI_TRACK_CMD_LIST    0x300000        /* Track active cmd list nodes,
						* करोne with reference to TID,
						* hence TRACK_TID also enabled.
						*/
#घोषणा QEDI_LOG_NOTICE		0x40000000	/* Notice logs */
#घोषणा QEDI_LOG_WARN		0x80000000	/* Warning logs */

/* Debug context काष्ठाure */
काष्ठा qedi_dbg_ctx अणु
	अचिन्हित पूर्णांक host_no;
	काष्ठा pci_dev *pdev;
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *bdf_dentry;
#पूर्ण_अगर
पूर्ण;

#घोषणा QEDI_ERR(pdev, fmt, ...)	\
		qedi_dbg_err(pdev, __func__, __LINE__, fmt, ## __VA_ARGS__)
#घोषणा QEDI_WARN(pdev, fmt, ...)	\
		qedi_dbg_warn(pdev, __func__, __LINE__, fmt, ## __VA_ARGS__)
#घोषणा QEDI_NOTICE(pdev, fmt, ...)	\
		qedi_dbg_notice(pdev, __func__, __LINE__, fmt, ## __VA_ARGS__)
#घोषणा QEDI_INFO(pdev, level, fmt, ...)	\
		qedi_dbg_info(pdev, __func__, __LINE__, level, fmt,	\
			      ## __VA_ARGS__)

व्योम qedi_dbg_err(काष्ठा qedi_dbg_ctx *qedi, स्थिर अक्षर *func, u32 line,
		  स्थिर अक्षर *fmt, ...);
व्योम qedi_dbg_warn(काष्ठा qedi_dbg_ctx *qedi, स्थिर अक्षर *func, u32 line,
		   स्थिर अक्षर *fmt, ...);
व्योम qedi_dbg_notice(काष्ठा qedi_dbg_ctx *qedi, स्थिर अक्षर *func, u32 line,
		     स्थिर अक्षर *fmt, ...);
व्योम qedi_dbg_info(काष्ठा qedi_dbg_ctx *qedi, स्थिर अक्षर *func, u32 line,
		   u32 info, स्थिर अक्षर *fmt, ...);

काष्ठा Scsi_Host;

काष्ठा sysfs_bin_attrs अणु
	अक्षर *name;
	काष्ठा bin_attribute *attr;
पूर्ण;

पूर्णांक qedi_create_sysfs_attr(काष्ठा Scsi_Host *shost,
			   काष्ठा sysfs_bin_attrs *iter);
व्योम qedi_हटाओ_sysfs_attr(काष्ठा Scsi_Host *shost,
			    काष्ठा sysfs_bin_attrs *iter);

/* DebugFS related code */
काष्ठा qedi_list_of_funcs अणु
	अक्षर *oper_str;
	sमाप_प्रकार (*oper_func)(काष्ठा qedi_dbg_ctx *qedi);
पूर्ण;

काष्ठा qedi_debugfs_ops अणु
	अक्षर *name;
	काष्ठा qedi_list_of_funcs *qedi_funcs;
पूर्ण;

#घोषणा qedi_dbg_fileops(drv, ops) \
अणु \
	.owner  = THIS_MODULE, \
	.खोलो   = simple_खोलो, \
	.पढ़ो   = drv##_dbg_##ops##_cmd_पढ़ो, \
	.ग_लिखो  = drv##_dbg_##ops##_cmd_ग_लिखो \
पूर्ण

/* Used क्रम debugfs sequential files */
#घोषणा qedi_dbg_fileops_seq(drv, ops) \
अणु \
	.owner = THIS_MODULE, \
	.खोलो = drv##_dbg_##ops##_खोलो, \
	.पढ़ो = seq_पढ़ो, \
	.llseek = seq_lseek, \
	.release = single_release, \
पूर्ण

व्योम qedi_dbg_host_init(काष्ठा qedi_dbg_ctx *qedi,
			स्थिर काष्ठा qedi_debugfs_ops *करोps,
			स्थिर काष्ठा file_operations *fops);
व्योम qedi_dbg_host_निकास(काष्ठा qedi_dbg_ctx *qedi);
व्योम qedi_dbg_init(अक्षर *drv_name);
व्योम qedi_dbg_निकास(व्योम);

#पूर्ण_अगर /* _QEDI_DBG_H_ */
