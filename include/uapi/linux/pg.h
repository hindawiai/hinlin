<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-1.0+ WITH Linux-syscall-note */
/* 	pg.h (c) 1998  Grant R. Guenther <grant@torque.net>
 		       Under the terms of the GNU General Public License


	pg.h defines the user पूर्णांकerface to the generic ATAPI packet
        command driver क्रम parallel port ATAPI devices (pg). The
	driver is loosely modelled after the generic SCSI driver, sg,
	although the actual पूर्णांकerface is dअगरferent.

	The pg driver provides a simple अक्षरacter device पूर्णांकerface क्रम
        sending ATAPI commands to a device.  With the exception of the
	ATAPI reset operation, all operations are perक्रमmed by a pair
        of पढ़ो and ग_लिखो operations to the appropriate /dev/pgN device.
	A ग_लिखो operation delivers a command and any outbound data in
        a single buffer.  Normally, the ग_लिखो will succeed unless the
        device is offline or malfunctioning, or there is alपढ़ोy another
	command pending.  If the ग_लिखो succeeds, it should be followed
        immediately by a पढ़ो operation, to obtain any वापसed data and
        status inक्रमmation.  A पढ़ो will fail अगर there is no operation
        in progress.

	As a special हाल, the device can be reset with a ग_लिखो operation,
        and in this हाल, no following पढ़ो is expected, or permitted.

	There are no ioctl() operations.  Any single operation
	may transfer at most PG_MAX_DATA bytes.  Note that the driver must
        copy the data through an पूर्णांकernal buffer.  In keeping with all
	current ATAPI devices, command packets are assumed to be exactly
	12 bytes in length.

	To permit future changes to this पूर्णांकerface, the headers in the
	पढ़ो and ग_लिखो buffers contain a single अक्षरacter "magic" flag.
        Currently this flag must be the अक्षरacter "P".

*/

#अगर_अघोषित _UAPI_LINUX_PG_H
#घोषणा _UAPI_LINUX_PG_H

#घोषणा PG_MAGIC	'P'
#घोषणा PG_RESET	'Z'
#घोषणा PG_COMMAND	'C'

#घोषणा PG_MAX_DATA	32768

काष्ठा pg_ग_लिखो_hdr अणु

	अक्षर	magic;		/* == PG_MAGIC */
	अक्षर	func;		/* PG_RESET or PG_COMMAND */
	पूर्णांक     dlen;		/* number of bytes expected to transfer */
	पूर्णांक     समयout;	/* number of seconds beक्रमe समयout */
	अक्षर	packet[12];	/* packet command */

पूर्ण;

काष्ठा pg_पढ़ो_hdr अणु

	अक्षर	magic;		/* == PG_MAGIC */
	अक्षर	scsi;		/* "scsi" status == sense key */
	पूर्णांक	dlen;		/* size of device transfer request */
	पूर्णांक     duration;	/* समय in seconds command took */
	अक्षर    pad[12];	/* not used */

पूर्ण;

#पूर्ण_अगर /* _UAPI_LINUX_PG_H */
