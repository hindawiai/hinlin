<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This header declares the utility functions used by "Gadget Zero", plus
 * पूर्णांकerfaces to its two single-configuration function drivers.
 */

#अगर_अघोषित __G_ZERO_H
#घोषणा __G_ZERO_H

#घोषणा GZERO_BULK_BUFLEN	4096
#घोषणा GZERO_QLEN		32
#घोषणा GZERO_ISOC_INTERVAL	4
#घोषणा GZERO_ISOC_MAXPACKET	1024
#घोषणा GZERO_SS_BULK_QLEN	1
#घोषणा GZERO_SS_ISO_QLEN	8

काष्ठा usb_zero_options अणु
	अचिन्हित pattern;
	अचिन्हित isoc_पूर्णांकerval;
	अचिन्हित isoc_maxpacket;
	अचिन्हित isoc_mult;
	अचिन्हित isoc_maxburst;
	अचिन्हित bulk_buflen;
	अचिन्हित qlen;
	अचिन्हित ss_bulk_qlen;
	अचिन्हित ss_iso_qlen;
पूर्ण;

काष्ठा f_ss_opts अणु
	काष्ठा usb_function_instance func_inst;
	अचिन्हित pattern;
	अचिन्हित isoc_पूर्णांकerval;
	अचिन्हित isoc_maxpacket;
	अचिन्हित isoc_mult;
	अचिन्हित isoc_maxburst;
	अचिन्हित bulk_buflen;
	अचिन्हित bulk_qlen;
	अचिन्हित iso_qlen;

	/*
	 * Read/ग_लिखो access to configfs attributes is handled by configfs.
	 *
	 * This is to protect the data from concurrent access by पढ़ो/ग_लिखो
	 * and create symlink/हटाओ symlink.
	 */
	काष्ठा mutex			lock;
	पूर्णांक				refcnt;
पूर्ण;

काष्ठा f_lb_opts अणु
	काष्ठा usb_function_instance func_inst;
	अचिन्हित bulk_buflen;
	अचिन्हित qlen;

	/*
	 * Read/ग_लिखो access to configfs attributes is handled by configfs.
	 *
	 * This is to protect the data from concurrent access by पढ़ो/ग_लिखो
	 * and create symlink/हटाओ symlink.
	 */
	काष्ठा mutex			lock;
	पूर्णांक				refcnt;
पूर्ण;

व्योम lb_modनिकास(व्योम);
पूर्णांक lb_modinit(व्योम);

/* common utilities */
व्योम disable_endpoपूर्णांकs(काष्ठा usb_composite_dev *cdev,
		काष्ठा usb_ep *in, काष्ठा usb_ep *out,
		काष्ठा usb_ep *iso_in, काष्ठा usb_ep *iso_out);

#पूर्ण_अगर /* __G_ZERO_H */
