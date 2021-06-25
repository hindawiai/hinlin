<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Basic KB3310B Embedded Controller support क्रम the YeeLoong 2F netbook
 *
 *  Copyright (C) 2008 Lemote Inc.
 *  Author: liujl <liujl@lemote.com>, 2008-04-20
 */

#समावेश <linux/पन.स>
#समावेश <linux/export.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>

#समावेश "ec_kb3310b.h"

अटल DEFINE_SPINLOCK(index_access_lock);
अटल DEFINE_SPINLOCK(port_access_lock);

अचिन्हित अक्षर ec_पढ़ो(अचिन्हित लघु addr)
अणु
	अचिन्हित अक्षर value;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&index_access_lock, flags);
	outb((addr & 0xff00) >> 8, EC_IO_PORT_HIGH);
	outb((addr & 0x00ff), EC_IO_PORT_LOW);
	value = inb(EC_IO_PORT_DATA);
	spin_unlock_irqrestore(&index_access_lock, flags);

	वापस value;
पूर्ण
EXPORT_SYMBOL_GPL(ec_पढ़ो);

व्योम ec_ग_लिखो(अचिन्हित लघु addr, अचिन्हित अक्षर val)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&index_access_lock, flags);
	outb((addr & 0xff00) >> 8, EC_IO_PORT_HIGH);
	outb((addr & 0x00ff), EC_IO_PORT_LOW);
	outb(val, EC_IO_PORT_DATA);
	/*  flush the ग_लिखो action */
	inb(EC_IO_PORT_DATA);
	spin_unlock_irqrestore(&index_access_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ec_ग_लिखो);

/*
 * This function is used क्रम EC command ग_लिखोs and corresponding status queries.
 */
पूर्णांक ec_query_seq(अचिन्हित अक्षर cmd)
अणु
	पूर्णांक समयout;
	अचिन्हित अक्षर status;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&port_access_lock, flags);

	/* make chip जाओ reset mode */
	udelay(EC_REG_DELAY);
	outb(cmd, EC_CMD_PORT);
	udelay(EC_REG_DELAY);

	/* check अगर the command is received by ec */
	समयout = EC_CMD_TIMEOUT;
	status = inb(EC_STS_PORT);
	जबतक (समयout-- && (status & (1 << 1))) अणु
		status = inb(EC_STS_PORT);
		udelay(EC_REG_DELAY);
	पूर्ण

	spin_unlock_irqrestore(&port_access_lock, flags);

	अगर (समयout <= 0) अणु
		prपूर्णांकk(KERN_ERR "%s: deadable error : timeout...\n", __func__);
		ret = -EINVAL;
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_INFO
			   "(%x/%d)ec issued command %d status : 0x%x\n",
			   समयout, EC_CMD_TIMEOUT - समयout, cmd, status);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ec_query_seq);

/*
 * Send query command to EC to get the proper event number
 */
पूर्णांक ec_query_event_num(व्योम)
अणु
	वापस ec_query_seq(CMD_GET_EVENT_NUM);
पूर्ण
EXPORT_SYMBOL(ec_query_event_num);

/*
 * Get event number from EC
 *
 * NOTE: This routine must follow the query_event_num function in the
 * पूर्णांकerrupt.
 */
पूर्णांक ec_get_event_num(व्योम)
अणु
	पूर्णांक समयout = 100;
	अचिन्हित अक्षर value;
	अचिन्हित अक्षर status;

	udelay(EC_REG_DELAY);
	status = inb(EC_STS_PORT);
	udelay(EC_REG_DELAY);
	जबतक (समयout-- && !(status & (1 << 0))) अणु
		status = inb(EC_STS_PORT);
		udelay(EC_REG_DELAY);
	पूर्ण
	अगर (समयout <= 0) अणु
		pr_info("%s: get event number timeout.\n", __func__);

		वापस -EINVAL;
	पूर्ण
	value = inb(EC_DAT_PORT);
	udelay(EC_REG_DELAY);

	वापस value;
पूर्ण
EXPORT_SYMBOL(ec_get_event_num);
