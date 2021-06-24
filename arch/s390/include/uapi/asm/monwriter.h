<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright IBM Corp. 2006
 * Character device driver क्रम writing z/VM APPLDATA monitor records
 * Version 1.0
 * Author(s): Melissa Howland <melissah@us.ibm.com>
 *
 */

#अगर_अघोषित _ASM_390_MONWRITER_H
#घोषणा _ASM_390_MONWRITER_H

/* mon_function values */
#घोषणा MONWRITE_START_INTERVAL	0x00 /* start पूर्णांकerval recording */
#घोषणा MONWRITE_STOP_INTERVAL	0x01 /* stop पूर्णांकerval or config recording */
#घोषणा MONWRITE_GEN_EVENT	0x02 /* generate event record */
#घोषणा MONWRITE_START_CONFIG	0x03 /* start configuration recording */

/* the header the app uses in its ग_लिखो() data */
काष्ठा monग_लिखो_hdr अणु
	अचिन्हित अक्षर mon_function;
	अचिन्हित लघु applid;
	अचिन्हित अक्षर record_num;
	अचिन्हित लघु version;
	अचिन्हित लघु release;
	अचिन्हित लघु mod_level;
	अचिन्हित लघु datalen;
	अचिन्हित अक्षर hdrlen;

पूर्ण __attribute__((packed));

#पूर्ण_अगर /* _ASM_390_MONWRITER_H */
