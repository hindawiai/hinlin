<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *   CIO inject पूर्णांकerface
 *
 *    Copyright IBM Corp. 2021
 *    Author(s): Vineeth Vijayan <vneethv@linux.ibm.com>
 */

#घोषणा KMSG_COMPONENT "cio"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mm.h>
#समावेश <linux/debugfs.h>
#समावेश <यंत्र/chpid.h>

#समावेश "cio_inject.h"
#समावेश "cio_debug.h"

अटल DEFINE_SPINLOCK(crw_inject_lock);
DEFINE_STATIC_KEY_FALSE(cio_inject_enabled);
अटल काष्ठा crw *crw_inject_data;

/**
 * crw_inject : Initiate the artअगरicial CRW inject
 * @crw: The data which needs to be injected as new CRW.
 *
 * The CRW handler is called, which will use the provided artअगरicial
 * data instead of the CRW from the underlying hardware.
 *
 * Return: 0 on success
 */
अटल पूर्णांक crw_inject(काष्ठा crw *crw)
अणु
	पूर्णांक rc = 0;
	काष्ठा crw *copy;
	अचिन्हित दीर्घ flags;

	copy = kmemdup(crw, माप(*crw), GFP_KERNEL);
	अगर (!copy)
		वापस -ENOMEM;

	spin_lock_irqsave(&crw_inject_lock, flags);
	अगर (crw_inject_data) अणु
		kमुक्त(copy);
		rc = -EBUSY;
	पूर्ण अन्यथा अणु
		crw_inject_data = copy;
	पूर्ण
	spin_unlock_irqrestore(&crw_inject_lock, flags);

	अगर (!rc)
		crw_handle_channel_report();

	वापस rc;
पूर्ण

/**
 * stcrw_get_injected: Copy the artअगरicial CRW data to CRW काष्ठा.
 * @crw: The target CRW poपूर्णांकer.
 *
 * Retrieve an injected CRW data. Return 0 on success, 1 अगर no
 * injected-CRW is available. The function reproduces the वापस
 * code of the actual STCRW function.
 */
पूर्णांक stcrw_get_injected(काष्ठा crw *crw)
अणु
	पूर्णांक rc = 1;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&crw_inject_lock, flags);
	अगर (crw_inject_data) अणु
		स_नकल(crw, crw_inject_data, माप(*crw));
		kमुक्त(crw_inject_data);
		crw_inject_data = शून्य;
		rc = 0;
	पूर्ण
	spin_unlock_irqrestore(&crw_inject_lock, flags);

	वापस rc;
पूर्ण

/* The debugfs ग_लिखो handler क्रम crw_inject nodes operation */
अटल sमाप_प्रकार crw_inject_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				माप_प्रकार lbuf, loff_t *ppos)
अणु
	u32 slct, oflw, chn, rsc, anc, erc, rsid;
	काष्ठा crw crw;
	अक्षर *buffer;
	पूर्णांक rc;

	अगर (!अटल_branch_likely(&cio_inject_enabled)) अणु
		pr_warn("CIO inject is not enabled - ignoring CRW inject\n");
		वापस -EINVAL;
	पूर्ण

	buffer = vmemdup_user(buf, lbuf);
	अगर (IS_ERR(buffer))
		वापस -ENOMEM;

	rc = माला_पूछो(buffer, "%x %x %x %x %x %x %x", &slct, &oflw, &chn, &rsc, &anc,
		    &erc, &rsid);

	kvमुक्त(buffer);
	अगर (rc != 7) अणु
		pr_warn("crw_inject: Invalid format (need <solicited> <overflow> <chaining> <rsc> <ancillary> <erc> <rsid>)\n");
		वापस -EINVAL;
	पूर्ण

	स_रखो(&crw, 0, माप(crw));
	crw.slct = slct;
	crw.oflw = oflw;
	crw.chn = chn;
	crw.rsc = rsc;
	crw.anc = anc;
	crw.erc = erc;
	crw.rsid = rsid;

	rc = crw_inject(&crw);
	अगर (rc)
		वापस rc;

	वापस lbuf;
पूर्ण

/* Debugfs ग_लिखो handler क्रम inject_enable node*/
अटल sमाप_प्रकार enable_inject_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				   माप_प्रकार lbuf, loff_t *ppos)
अणु
	अचिन्हित दीर्घ en = 0;
	पूर्णांक rc;

	rc = kम_से_अदीर्घ_from_user(buf, lbuf, 10, &en);
	अगर (rc)
		वापस rc;

	चयन (en) अणु
	हाल 0:
		अटल_branch_disable(&cio_inject_enabled);
		अवरोध;
	हाल 1:
		अटल_branch_enable(&cio_inject_enabled);
		अवरोध;
	पूर्ण

	वापस lbuf;
पूर्ण

अटल स्थिर काष्ठा file_operations crw_fops = अणु
	.owner = THIS_MODULE,
	.ग_लिखो = crw_inject_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा file_operations cio_en_fops = अणु
	.owner = THIS_MODULE,
	.ग_लिखो = enable_inject_ग_लिखो,
पूर्ण;

अटल पूर्णांक __init cio_inject_init(व्योम)
अणु
	/* enable_inject node enables the अटल branching */
	debugfs_create_file("enable_inject", 0200, cio_debugfs_dir,
			    शून्य, &cio_en_fops);

	debugfs_create_file("crw_inject", 0200, cio_debugfs_dir,
			    शून्य, &crw_fops);
	वापस 0;
पूर्ण

device_initcall(cio_inject_init);
