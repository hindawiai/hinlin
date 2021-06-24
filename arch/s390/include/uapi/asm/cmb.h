<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPIS390_CMB_H
#घोषणा _UAPIS390_CMB_H

#समावेश <linux/types.h>

/**
 * काष्ठा cmbdata - channel measurement block data क्रम user space
 * @size: size of the stored data
 * @elapsed_समय: समय since last sampling
 * @ssch_rsch_count: number of ssch and rsch
 * @sample_count: number of samples
 * @device_connect_समय: समय of device connect
 * @function_pending_समय: समय of function pending
 * @device_disconnect_समय: समय of device disconnect
 * @control_unit_queuing_समय: समय of control unit queuing
 * @device_active_only_समय: समय of device active only
 * @device_busy_समय: समय of device busy (ext. क्रमmat)
 * @initial_command_response_समय: initial command response समय (ext. क्रमmat)
 *
 * All values are stored as 64 bit क्रम simplicity, especially
 * in 32 bit emulation mode. All समय values are normalized to
 * nanoseconds.
 * Currently, two क्रमmats are known, which dअगरfer by the size of
 * this काष्ठाure, i.e. the last two members are only set when
 * the extended channel measurement facility (first shipped in
 * z990 machines) is activated.
 * Potentially, more fields could be added, which would result in a
 * new ioctl number.
 */
काष्ठा cmbdata अणु
	__u64 size;
	__u64 elapsed_समय;
 /* basic and exended क्रमmat: */
	__u64 ssch_rsch_count;
	__u64 sample_count;
	__u64 device_connect_समय;
	__u64 function_pending_समय;
	__u64 device_disconnect_समय;
	__u64 control_unit_queuing_समय;
	__u64 device_active_only_समय;
 /* extended क्रमmat only: */
	__u64 device_busy_समय;
	__u64 initial_command_response_समय;
पूर्ण;

/* enable channel measurement */
#घोषणा BIODASDCMFENABLE	_IO(DASD_IOCTL_LETTER, 32)
/* enable channel measurement */
#घोषणा BIODASDCMFDISABLE	_IO(DASD_IOCTL_LETTER, 33)
/* पढ़ो channel measurement data */
#घोषणा BIODASDREADALLCMB	_IOWR(DASD_IOCTL_LETTER, 33, काष्ठा cmbdata)

#पूर्ण_अगर /* _UAPIS390_CMB_H */
