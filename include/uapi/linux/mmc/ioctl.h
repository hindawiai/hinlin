<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित LINUX_MMC_IOCTL_H
#घोषणा LINUX_MMC_IOCTL_H

#समावेश <linux/types.h>
#समावेश <linux/major.h>

काष्ठा mmc_ioc_cmd अणु
	/*
	 * Direction of data: nonzero = ग_लिखो, zero = पढ़ो.
	 * Bit 31 selects 'Reliable Write' क्रम RPMB.
	 */
	पूर्णांक ग_लिखो_flag;

	/* Application-specअगरic command.  true = precede with CMD55 */
	पूर्णांक is_acmd;

	__u32 opcode;
	__u32 arg;
	__u32 response[4];  /* CMD response */
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक blksz;
	अचिन्हित पूर्णांक blocks;

	/*
	 * Sleep at least postsleep_min_us useconds, and at most
	 * postsleep_max_us useconds *after* issuing command.  Needed क्रम
	 * some पढ़ो commands क्रम which cards have no other way of indicating
	 * they're पढ़ोy क्रम the next command (i.e. there is no equivalent of
	 * a "busy" indicator क्रम पढ़ो operations).
	 */
	अचिन्हित पूर्णांक postsleep_min_us;
	अचिन्हित पूर्णांक postsleep_max_us;

	/*
	 * Override driver-computed समयouts.  Note the dअगरference in units!
	 */
	अचिन्हित पूर्णांक data_समयout_ns;
	अचिन्हित पूर्णांक cmd_समयout_ms;

	/*
	 * For 64-bit machines, the next member, ``__u64 data_ptr``, wants to
	 * be 8-byte aligned.  Make sure this काष्ठा is the same size when
	 * built क्रम 32-bit.
	 */
	__u32 __pad;

	/* DAT buffer */
	__u64 data_ptr;
पूर्ण;
#घोषणा mmc_ioc_cmd_set_data(ic, ptr) ic.data_ptr = (__u64)(अचिन्हित दीर्घ) ptr

/**
 * काष्ठा mmc_ioc_multi_cmd - multi command inक्रमmation
 * @num_of_cmds: Number of commands to send. Must be equal to or less than
 *	MMC_IOC_MAX_CMDS.
 * @cmds: Array of commands with length equal to 'num_of_cmds'
 */
काष्ठा mmc_ioc_multi_cmd अणु
	__u64 num_of_cmds;
	काष्ठा mmc_ioc_cmd cmds[0];
पूर्ण;

#घोषणा MMC_IOC_CMD _IOWR(MMC_BLOCK_MAJOR, 0, काष्ठा mmc_ioc_cmd)
/*
 * MMC_IOC_MULTI_CMD: Used to send an array of MMC commands described by
 *	the काष्ठाure mmc_ioc_multi_cmd. The MMC driver will issue all
 *	commands in array in sequence to card.
 */
#घोषणा MMC_IOC_MULTI_CMD _IOWR(MMC_BLOCK_MAJOR, 1, काष्ठा mmc_ioc_multi_cmd)
/*
 * Since this ioctl is only meant to enhance (and not replace) normal access
 * to the mmc bus device, an upper data transfer limit of MMC_IOC_MAX_BYTES
 * is enक्रमced per ioctl call.  For larger data transfers, use the normal
 * block device operations.
 */
#घोषणा MMC_IOC_MAX_BYTES  (512L * 1024)
#घोषणा MMC_IOC_MAX_CMDS    255
#पूर्ण_अगर /* LINUX_MMC_IOCTL_H */
