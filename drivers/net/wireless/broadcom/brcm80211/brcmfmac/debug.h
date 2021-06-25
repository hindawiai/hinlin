<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2010 Broadcom Corporation
 */

#अगर_अघोषित BRCMFMAC_DEBUG_H
#घोषणा BRCMFMAC_DEBUG_H

#समावेश <linux/net.h>	/* net_ratelimit() */

/* message levels */
#घोषणा BRCMF_TRACE_VAL		0x00000002
#घोषणा BRCMF_INFO_VAL		0x00000004
#घोषणा BRCMF_DATA_VAL		0x00000008
#घोषणा BRCMF_CTL_VAL		0x00000010
#घोषणा BRCMF_TIMER_VAL		0x00000020
#घोषणा BRCMF_HDRS_VAL		0x00000040
#घोषणा BRCMF_BYTES_VAL		0x00000080
#घोषणा BRCMF_INTR_VAL		0x00000100
#घोषणा BRCMF_GLOM_VAL		0x00000200
#घोषणा BRCMF_EVENT_VAL		0x00000400
#घोषणा BRCMF_BTA_VAL		0x00000800
#घोषणा BRCMF_FIL_VAL		0x00001000
#घोषणा BRCMF_USB_VAL		0x00002000
#घोषणा BRCMF_SCAN_VAL		0x00004000
#घोषणा BRCMF_CONN_VAL		0x00008000
#घोषणा BRCMF_BCDC_VAL		0x00010000
#घोषणा BRCMF_SDIO_VAL		0x00020000
#घोषणा BRCMF_MSGBUF_VAL	0x00040000
#घोषणा BRCMF_PCIE_VAL		0x00080000
#घोषणा BRCMF_FWCON_VAL		0x00100000

/* set शेष prपूर्णांक क्रमmat */
#अघोषित pr_fmt
#घोषणा pr_fmt(fmt)		KBUILD_MODNAME ": " fmt

काष्ठा brcmf_bus;

__म_लिखो(3, 4)
व्योम __brcmf_err(काष्ठा brcmf_bus *bus, स्थिर अक्षर *func, स्थिर अक्षर *fmt, ...);
/* Macro क्रम error messages. When debugging / tracing the driver all error
 * messages are important to us.
 */
#अगर_अघोषित brcmf_err
#घोषणा brcmf_err(fmt, ...)						\
	करो अणु								\
		अगर (IS_ENABLED(CONFIG_BRCMDBG) ||			\
		    IS_ENABLED(CONFIG_BRCM_TRACING) ||			\
		    net_ratelimit())					\
			__brcmf_err(शून्य, __func__, fmt, ##__VA_ARGS__);\
	पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा bphy_err(drvr, fmt, ...)					\
	करो अणु								\
		अगर (IS_ENABLED(CONFIG_BRCMDBG) ||			\
		    IS_ENABLED(CONFIG_BRCM_TRACING) ||			\
		    net_ratelimit())					\
			wiphy_err((drvr)->wiphy, "%s: " fmt, __func__,	\
				  ##__VA_ARGS__);			\
	पूर्ण जबतक (0)

#अगर defined(DEBUG) || defined(CONFIG_BRCM_TRACING)

/* For debug/tracing purposes treat info messages as errors */
#घोषणा brcmf_info brcmf_err

__म_लिखो(3, 4)
व्योम __brcmf_dbg(u32 level, स्थिर अक्षर *func, स्थिर अक्षर *fmt, ...);
#घोषणा brcmf_dbg(level, fmt, ...)				\
करो अणु								\
	__brcmf_dbg(BRCMF_##level##_VAL, __func__,		\
		    fmt, ##__VA_ARGS__);			\
पूर्ण जबतक (0)
#घोषणा BRCMF_DATA_ON()		(brcmf_msg_level & BRCMF_DATA_VAL)
#घोषणा BRCMF_CTL_ON()		(brcmf_msg_level & BRCMF_CTL_VAL)
#घोषणा BRCMF_HDRS_ON()		(brcmf_msg_level & BRCMF_HDRS_VAL)
#घोषणा BRCMF_BYTES_ON()	(brcmf_msg_level & BRCMF_BYTES_VAL)
#घोषणा BRCMF_GLOM_ON()		(brcmf_msg_level & BRCMF_GLOM_VAL)
#घोषणा BRCMF_EVENT_ON()	(brcmf_msg_level & BRCMF_EVENT_VAL)
#घोषणा BRCMF_FIL_ON()		(brcmf_msg_level & BRCMF_FIL_VAL)
#घोषणा BRCMF_FWCON_ON()	(brcmf_msg_level & BRCMF_FWCON_VAL)
#घोषणा BRCMF_SCAN_ON()		(brcmf_msg_level & BRCMF_SCAN_VAL)

#अन्यथा /* defined(DEBUG) || defined(CONFIG_BRCM_TRACING) */

#घोषणा brcmf_info(fmt, ...)						\
	करो अणु								\
		pr_info("%s: " fmt, __func__, ##__VA_ARGS__);		\
	पूर्ण जबतक (0)

#घोषणा brcmf_dbg(level, fmt, ...) no_prपूर्णांकk(fmt, ##__VA_ARGS__)

#घोषणा BRCMF_DATA_ON()		0
#घोषणा BRCMF_CTL_ON()		0
#घोषणा BRCMF_HDRS_ON()		0
#घोषणा BRCMF_BYTES_ON()	0
#घोषणा BRCMF_GLOM_ON()		0
#घोषणा BRCMF_EVENT_ON()	0
#घोषणा BRCMF_FIL_ON()		0
#घोषणा BRCMF_FWCON_ON()	0
#घोषणा BRCMF_SCAN_ON()		0

#पूर्ण_अगर /* defined(DEBUG) || defined(CONFIG_BRCM_TRACING) */

#घोषणा brcmf_dbg_hex_dump(test, data, len, fmt, ...)			\
करो अणु									\
	trace_brcmf_hexdump((व्योम *)data, len);				\
	अगर (test)							\
		brcmu_dbg_hex_dump(data, len, fmt, ##__VA_ARGS__);	\
पूर्ण जबतक (0)

बाह्य पूर्णांक brcmf_msg_level;

काष्ठा brcmf_pub;
#अगर_घोषित DEBUG
काष्ठा dentry *brcmf_debugfs_get_devdir(काष्ठा brcmf_pub *drvr);
व्योम brcmf_debugfs_add_entry(काष्ठा brcmf_pub *drvr, स्थिर अक्षर *fn,
			     पूर्णांक (*पढ़ो_fn)(काष्ठा seq_file *seq, व्योम *data));
पूर्णांक brcmf_debug_create_memdump(काष्ठा brcmf_bus *bus, स्थिर व्योम *data,
			       माप_प्रकार len);
#अन्यथा
अटल अंतरभूत काष्ठा dentry *brcmf_debugfs_get_devdir(काष्ठा brcmf_pub *drvr)
अणु
	वापस ERR_PTR(-ENOENT);
पूर्ण
अटल अंतरभूत
व्योम brcmf_debugfs_add_entry(काष्ठा brcmf_pub *drvr, स्थिर अक्षर *fn,
			     पूर्णांक (*पढ़ो_fn)(काष्ठा seq_file *seq, व्योम *data))
अणु पूर्ण
अटल अंतरभूत
पूर्णांक brcmf_debug_create_memdump(काष्ठा brcmf_bus *bus, स्थिर व्योम *data,
			       माप_प्रकार len)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* BRCMFMAC_DEBUG_H */
