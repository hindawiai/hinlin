<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_PAGE_REPORTING_H
#घोषणा _LINUX_PAGE_REPORTING_H

#समावेश <linux/mmzone.h>
#समावेश <linux/scatterlist.h>

/* This value should always be a घातer of 2, see page_reporting_cycle() */
#घोषणा PAGE_REPORTING_CAPACITY		32

काष्ठा page_reporting_dev_info अणु
	/* function that alters pages to make them "reported" */
	पूर्णांक (*report)(काष्ठा page_reporting_dev_info *prdev,
		      काष्ठा scatterlist *sg, अचिन्हित पूर्णांक nents);

	/* work काष्ठा क्रम processing reports */
	काष्ठा delayed_work work;

	/* Current state of page reporting */
	atomic_t state;
पूर्ण;

/* Tear-करोwn and bring-up क्रम page reporting devices */
व्योम page_reporting_unरेजिस्टर(काष्ठा page_reporting_dev_info *prdev);
पूर्णांक page_reporting_रेजिस्टर(काष्ठा page_reporting_dev_info *prdev);
#पूर्ण_अगर /*_LINUX_PAGE_REPORTING_H */
