<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  QLogic FCoE Offload Driver
 *  Copyright (c) 2016-2018 Cavium Inc.
 */
#अगर_अघोषित _QEDF_DBG_H_
#घोषणा _QEDF_DBG_H_

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/compiler.h>
#समावेश <linux/माला.स>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <linux/fs.h>

#समावेश <linux/qed/common_hsi.h>
#समावेश <linux/qed/qed_अगर.h>

बाह्य uपूर्णांक qedf_debug;

/* Debug prपूर्णांक level definitions */
#घोषणा QEDF_LOG_DEFAULT	0x1		/* Set शेष logging mask */
#घोषणा QEDF_LOG_INFO		0x2		/*
						 * Inक्रमmational logs,
						 * MAC address, WWPN, WWNN
						 */
#घोषणा QEDF_LOG_DISC		0x4		/* Init, discovery, rport */
#घोषणा QEDF_LOG_LL2		0x8		/* LL2, VLAN logs */
#घोषणा QEDF_LOG_CONN		0x10		/* Connection setup, cleanup */
#घोषणा QEDF_LOG_EVT		0x20		/* Events, link, mtu */
#घोषणा QEDF_LOG_TIMER		0x40		/* Timer events */
#घोषणा QEDF_LOG_MP_REQ	0x80		/* Middle Path (MP) logs */
#घोषणा QEDF_LOG_SCSI_TM	0x100		/* SCSI Aborts, Task Mgmt */
#घोषणा QEDF_LOG_UNSOL		0x200		/* unsolicited event logs */
#घोषणा QEDF_LOG_IO		0x400		/* scsi cmd, completion */
#घोषणा QEDF_LOG_MQ		0x800		/* Multi Queue logs */
#घोषणा QEDF_LOG_BSG		0x1000		/* BSG logs */
#घोषणा QEDF_LOG_DEBUGFS	0x2000		/* debugFS logs */
#घोषणा QEDF_LOG_LPORT		0x4000		/* lport logs */
#घोषणा QEDF_LOG_ELS		0x8000		/* ELS logs */
#घोषणा QEDF_LOG_NPIV		0x10000		/* NPIV logs */
#घोषणा QEDF_LOG_SESS		0x20000		/* Connection setup, cleanup */
#घोषणा QEDF_LOG_TID		0x80000         /*
						 * FW TID context acquire
						 * मुक्त
						 */
#घोषणा QEDF_TRACK_TID		0x100000        /*
						 * Track TID state. To be
						 * enabled only at module load
						 * and not run-समय.
						 */
#घोषणा QEDF_TRACK_CMD_LIST    0x300000        /*
						* Track active cmd list nodes,
						* करोne with reference to TID,
						* hence TRACK_TID also enabled.
						*/
#घोषणा QEDF_LOG_NOTICE	0x40000000	/* Notice logs */
#घोषणा QEDF_LOG_WARN		0x80000000	/* Warning logs */

/* Debug context काष्ठाure */
काष्ठा qedf_dbg_ctx अणु
	अचिन्हित पूर्णांक host_no;
	काष्ठा pci_dev *pdev;
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *bdf_dentry;
#पूर्ण_अगर
पूर्ण;

#घोषणा QEDF_ERR(pdev, fmt, ...)	\
		qedf_dbg_err(pdev, __func__, __LINE__, fmt, ## __VA_ARGS__)
#घोषणा QEDF_WARN(pdev, fmt, ...)	\
		qedf_dbg_warn(pdev, __func__, __LINE__, fmt, ## __VA_ARGS__)
#घोषणा QEDF_NOTICE(pdev, fmt, ...)	\
		qedf_dbg_notice(pdev, __func__, __LINE__, fmt, ## __VA_ARGS__)
#घोषणा QEDF_INFO(pdev, level, fmt, ...)	\
		qedf_dbg_info(pdev, __func__, __LINE__, level, fmt,	\
			      ## __VA_ARGS__)
__म_लिखो(4, 5)
व्योम qedf_dbg_err(काष्ठा qedf_dbg_ctx *qedf, स्थिर अक्षर *func, u32 line,
			  स्थिर अक्षर *fmt, ...);
__म_लिखो(4, 5)
व्योम qedf_dbg_warn(काष्ठा qedf_dbg_ctx *qedf, स्थिर अक्षर *func, u32 line,
			   स्थिर अक्षर *, ...);
__म_लिखो(4, 5)
व्योम qedf_dbg_notice(काष्ठा qedf_dbg_ctx *qedf, स्थिर अक्षर *func,
			    u32 line, स्थिर अक्षर *, ...);
__म_लिखो(5, 6)
व्योम qedf_dbg_info(काष्ठा qedf_dbg_ctx *qedf, स्थिर अक्षर *func, u32 line,
			  u32 info, स्थिर अक्षर *fmt, ...);

/* GRC Dump related defines */

काष्ठा Scsi_Host;

#घोषणा QEDF_UEVENT_CODE_GRCDUMP 0

काष्ठा sysfs_bin_attrs अणु
	अक्षर *name;
	काष्ठा bin_attribute *attr;
पूर्ण;

बाह्य पूर्णांक qedf_alloc_grc_dump_buf(uपूर्णांक8_t **buf, uपूर्णांक32_t len);
बाह्य व्योम qedf_मुक्त_grc_dump_buf(uपूर्णांक8_t **buf);
बाह्य पूर्णांक qedf_get_grc_dump(काष्ठा qed_dev *cdev,
			     स्थिर काष्ठा qed_common_ops *common, uपूर्णांक8_t **buf,
			     uपूर्णांक32_t *grcsize);
बाह्य व्योम qedf_uevent_emit(काष्ठा Scsi_Host *shost, u32 code, अक्षर *msg);
बाह्य पूर्णांक qedf_create_sysfs_attr(काष्ठा Scsi_Host *shost,
				   काष्ठा sysfs_bin_attrs *iter);
बाह्य व्योम qedf_हटाओ_sysfs_attr(काष्ठा Scsi_Host *shost,
				    काष्ठा sysfs_bin_attrs *iter);

काष्ठा qedf_debugfs_ops अणु
	अक्षर *name;
	काष्ठा qedf_list_of_funcs *qedf_funcs;
पूर्ण;

बाह्य स्थिर काष्ठा qedf_debugfs_ops qedf_debugfs_ops[];
बाह्य स्थिर काष्ठा file_operations qedf_dbg_fops[];

#अगर_घोषित CONFIG_DEBUG_FS
/* DebugFS related code */
काष्ठा qedf_list_of_funcs अणु
	अक्षर *oper_str;
	sमाप_प्रकार (*oper_func)(काष्ठा qedf_dbg_ctx *qedf);
पूर्ण;

#घोषणा qedf_dbg_fileops(drv, ops) \
अणु \
	.owner  = THIS_MODULE, \
	.खोलो   = simple_खोलो, \
	.पढ़ो   = drv##_dbg_##ops##_cmd_पढ़ो, \
	.ग_लिखो  = drv##_dbg_##ops##_cmd_ग_लिखो \
पूर्ण

/* Used क्रम debugfs sequential files */
#घोषणा qedf_dbg_fileops_seq(drv, ops) \
अणु \
	.owner = THIS_MODULE, \
	.खोलो = drv##_dbg_##ops##_खोलो, \
	.पढ़ो = seq_पढ़ो, \
	.llseek = seq_lseek, \
	.release = single_release, \
पूर्ण

बाह्य व्योम qedf_dbg_host_init(काष्ठा qedf_dbg_ctx *qedf,
				स्थिर काष्ठा qedf_debugfs_ops *करोps,
				स्थिर काष्ठा file_operations *fops);
बाह्य व्योम qedf_dbg_host_निकास(काष्ठा qedf_dbg_ctx *qedf);
बाह्य व्योम qedf_dbg_init(अक्षर *drv_name);
बाह्य व्योम qedf_dbg_निकास(व्योम);
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

#पूर्ण_अगर /* _QEDF_DBG_H_ */
