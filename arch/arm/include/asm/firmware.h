<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Samsung Electronics.
 * Kyungmin Park <kyungmin.park@samsung.com>
 * Tomasz Figa <t.figa@samsung.com>
 */

#अगर_अघोषित __ASM_ARM_FIRMWARE_H
#घोषणा __ASM_ARM_FIRMWARE_H

#समावेश <linux/bug.h>

/*
 * काष्ठा firmware_ops
 *
 * A काष्ठाure to specअगरy available firmware operations.
 *
 * A filled up काष्ठाure can be रेजिस्टरed with रेजिस्टर_firmware_ops().
 */
काष्ठा firmware_ops अणु
	/*
	 * Inक्रमm the firmware we पूर्णांकend to enter CPU idle mode
	 */
	पूर्णांक (*prepare_idle)(अचिन्हित दीर्घ mode);
	/*
	 * Enters CPU idle mode
	 */
	पूर्णांक (*करो_idle)(अचिन्हित दीर्घ mode);
	/*
	 * Sets boot address of specअगरied physical CPU
	 */
	पूर्णांक (*set_cpu_boot_addr)(पूर्णांक cpu, अचिन्हित दीर्घ boot_addr);
	/*
	 * Gets boot address of specअगरied physical CPU
	 */
	पूर्णांक (*get_cpu_boot_addr)(पूर्णांक cpu, अचिन्हित दीर्घ *boot_addr);
	/*
	 * Boots specअगरied physical CPU
	 */
	पूर्णांक (*cpu_boot)(पूर्णांक cpu);
	/*
	 * Initializes L2 cache
	 */
	पूर्णांक (*l2x0_init)(व्योम);
	/*
	 * Enter प्रणाली-wide suspend.
	 */
	पूर्णांक (*suspend)(व्योम);
	/*
	 * Restore state of privileged hardware after प्रणाली-wide suspend.
	 */
	पूर्णांक (*resume)(व्योम);
पूर्ण;

/* Global poपूर्णांकer क्रम current firmware_ops काष्ठाure, can't be शून्य. */
बाह्य स्थिर काष्ठा firmware_ops *firmware_ops;

/*
 * call_firmware_op(op, ...)
 *
 * Checks अगर firmware operation is present and calls it,
 * otherwise वापसs -ENOSYS
 */
#घोषणा call_firmware_op(op, ...)					\
	((firmware_ops->op) ? firmware_ops->op(__VA_ARGS__) : (-ENOSYS))

/*
 * रेजिस्टर_firmware_ops(ops)
 *
 * A function to रेजिस्टर platक्रमm firmware_ops काष्ठा.
 */
अटल अंतरभूत व्योम रेजिस्टर_firmware_ops(स्थिर काष्ठा firmware_ops *ops)
अणु
	BUG_ON(!ops);

	firmware_ops = ops;
पूर्ण

#पूर्ण_अगर
