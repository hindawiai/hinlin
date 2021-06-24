<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Silicon Lअसल C2 port Linux support
 *
 *  Copyright (c) 2007 Roकरोlfo Giometti <giometti@linux.it>
 *  Copyright (c) 2007 Eurotech S.p.A. <info@eurotech.it>
 */

#घोषणा C2PORT_NAME_LEN			32

काष्ठा device;

/*
 * C2 port basic काष्ठाs
 */

/* Main काष्ठा */
काष्ठा c2port_ops;
काष्ठा c2port_device अणु
	अचिन्हित पूर्णांक access:1;
	अचिन्हित पूर्णांक flash_access:1;

	पूर्णांक id;
	अक्षर name[C2PORT_NAME_LEN];
	काष्ठा c2port_ops *ops;
	काष्ठा mutex mutex;		/* prevent races during पढ़ो/ग_लिखो */

	काष्ठा device *dev;

	व्योम *निजी_data;
पूर्ण;

/* Basic operations */
काष्ठा c2port_ops अणु
	/* Flash layout */
	अचिन्हित लघु block_size;	/* flash block size in bytes */
	अचिन्हित लघु blocks_num;	/* flash blocks number */

	/* Enable or disable the access to C2 port */
	व्योम (*access)(काष्ठा c2port_device *dev, पूर्णांक status);

	/* Set C2D data line as input/output */
	व्योम (*c2d_dir)(काष्ठा c2port_device *dev, पूर्णांक dir);

	/* Read/ग_लिखो C2D data line */
	पूर्णांक (*c2d_get)(काष्ठा c2port_device *dev);
	व्योम (*c2d_set)(काष्ठा c2port_device *dev, पूर्णांक status);

	/* Write C2CK घड़ी line */
	व्योम (*c2ck_set)(काष्ठा c2port_device *dev, पूर्णांक status);
पूर्ण;

/*
 * Exported functions
 */

बाह्य काष्ठा c2port_device *c2port_device_रेजिस्टर(अक्षर *name,
					काष्ठा c2port_ops *ops, व्योम *devdata);
बाह्य व्योम c2port_device_unरेजिस्टर(काष्ठा c2port_device *dev);
