<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Device driver क्रम s390 storage class memory.
 *
 * Copyright IBM Corp. 2012
 * Author(s): Sebastian Ott <sebott@linux.vnet.ibm.com>
 */

#घोषणा KMSG_COMPONENT "scm_block"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/eadm.h>
#समावेश "scm_blk.h"

अटल व्योम scm_notअगरy(काष्ठा scm_device *scmdev, क्रमागत scm_event event)
अणु
	काष्ठा scm_blk_dev *bdev = dev_get_drvdata(&scmdev->dev);

	चयन (event) अणु
	हाल SCM_CHANGE:
		pr_info("%lx: The capabilities of the SCM increment changed\n",
			(अचिन्हित दीर्घ) scmdev->address);
		SCM_LOG(2, "State changed");
		SCM_LOG_STATE(2, scmdev);
		अवरोध;
	हाल SCM_AVAIL:
		SCM_LOG(2, "Increment available");
		SCM_LOG_STATE(2, scmdev);
		scm_blk_set_available(bdev);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक scm_probe(काष्ठा scm_device *scmdev)
अणु
	काष्ठा scm_blk_dev *bdev;
	पूर्णांक ret;

	SCM_LOG(2, "probe");
	SCM_LOG_STATE(2, scmdev);

	अगर (scmdev->attrs.oper_state != OP_STATE_GOOD)
		वापस -EINVAL;

	bdev = kzalloc(माप(*bdev), GFP_KERNEL);
	अगर (!bdev)
		वापस -ENOMEM;

	dev_set_drvdata(&scmdev->dev, bdev);
	ret = scm_blk_dev_setup(bdev, scmdev);
	अगर (ret) अणु
		dev_set_drvdata(&scmdev->dev, शून्य);
		kमुक्त(bdev);
		जाओ out;
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल पूर्णांक scm_हटाओ(काष्ठा scm_device *scmdev)
अणु
	काष्ठा scm_blk_dev *bdev = dev_get_drvdata(&scmdev->dev);

	scm_blk_dev_cleanup(bdev);
	dev_set_drvdata(&scmdev->dev, शून्य);
	kमुक्त(bdev);

	वापस 0;
पूर्ण

अटल काष्ठा scm_driver scm_drv = अणु
	.drv = अणु
		.name = "scm_block",
		.owner = THIS_MODULE,
	पूर्ण,
	.notअगरy = scm_notअगरy,
	.probe = scm_probe,
	.हटाओ = scm_हटाओ,
	.handler = scm_blk_irq,
पूर्ण;

पूर्णांक __init scm_drv_init(व्योम)
अणु
	वापस scm_driver_रेजिस्टर(&scm_drv);
पूर्ण

व्योम scm_drv_cleanup(व्योम)
अणु
	scm_driver_unरेजिस्टर(&scm_drv);
पूर्ण
