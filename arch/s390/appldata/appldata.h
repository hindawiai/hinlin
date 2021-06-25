<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Definitions and पूर्णांकerface क्रम Linux - z/VM Monitor Stream.
 *
 * Copyright IBM Corp. 2003, 2008
 *
 * Author: Gerald Schaefer <gerald.schaefer@de.ibm.com>
 */

#घोषणा APPLDATA_MAX_REC_SIZE	  4024	/* Maximum size of the */
					/* data buffer */
#घोषणा APPLDATA_MAX_PROCS 100

#घोषणा APPLDATA_PROC_NAME_LENGTH 16	/* Max. length of /proc name */

#घोषणा APPLDATA_RECORD_MEM_ID		0x01	/* IDs to identअगरy the */
#घोषणा APPLDATA_RECORD_OS_ID		0x02	/* inभागidual records, */
#घोषणा APPLDATA_RECORD_NET_SUM_ID	0x03	/* must be < 256 !     */
#घोषणा APPLDATA_RECORD_PROC_ID		0x04

#घोषणा CTL_APPLDATA_TIMER 	2121	/* sysctl IDs, must be unique */
#घोषणा CTL_APPLDATA_INTERVAL 	2122
#घोषणा CTL_APPLDATA_MEM	2123
#घोषणा CTL_APPLDATA_OS		2124
#घोषणा CTL_APPLDATA_NET_SUM	2125
#घोषणा CTL_APPLDATA_PROC	2126

काष्ठा appldata_ops अणु
	काष्ठा list_head list;
	काष्ठा ctl_table_header *sysctl_header;
	काष्ठा ctl_table *ctl_table;
	पूर्णांक    active;				/* monitoring status */

	/* fill in from here */
	अक्षर name[APPLDATA_PROC_NAME_LENGTH];	/* name of /proc fs node */
	अचिन्हित अक्षर record_nr;		/* Record Nr. क्रम Product ID */
	व्योम (*callback)(व्योम *data);		/* callback function */
	व्योम *data;				/* record data */
	अचिन्हित पूर्णांक size;			/* size of record */
	काष्ठा module *owner;			/* THIS_MODULE */
	अक्षर mod_lvl[2];			/* modअगरication level, EBCDIC */
पूर्ण;

बाह्य पूर्णांक appldata_रेजिस्टर_ops(काष्ठा appldata_ops *ops);
बाह्य व्योम appldata_unरेजिस्टर_ops(काष्ठा appldata_ops *ops);
बाह्य पूर्णांक appldata_diag(अक्षर record_nr, u16 function, अचिन्हित दीर्घ buffer,
			 u16 length, अक्षर *mod_lvl);

