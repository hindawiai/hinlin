<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_SECUREBITS_H
#घोषणा _UAPI_LINUX_SECUREBITS_H

/* Each securesetting is implemented using two bits. One bit specअगरies
   whether the setting is on or off. The other bit specअगरy whether the
   setting is locked or not. A setting which is locked cannot be
   changed from user-level. */
#घोषणा issecure_mask(X)	(1 << (X))

#घोषणा SECUREBITS_DEFAULT 0x00000000

/* When set UID 0 has no special privileges. When unset, we support
   inheritance of root-permissions and suid-root executable under
   compatibility mode. We उठाओ the effective and inheritable biपंचांगasks
   *of the executable file* अगर the effective uid of the new process is
   0. If the real uid is 0, we उठाओ the effective (legacy) bit of the
   executable file. */
#घोषणा SECURE_NOROOT			0
#घोषणा SECURE_NOROOT_LOCKED		1  /* make bit-0 immutable */

#घोषणा SECBIT_NOROOT		(issecure_mask(SECURE_NOROOT))
#घोषणा SECBIT_NOROOT_LOCKED	(issecure_mask(SECURE_NOROOT_LOCKED))

/* When set, setuid to/from uid 0 करोes not trigger capability-"fixup".
   When unset, to provide compatiblility with old programs relying on
   set*uid to gain/lose privilege, transitions to/from uid 0 cause
   capabilities to be gained/lost. */
#घोषणा SECURE_NO_SETUID_FIXUP		2
#घोषणा SECURE_NO_SETUID_FIXUP_LOCKED	3  /* make bit-2 immutable */

#घोषणा SECBIT_NO_SETUID_FIXUP	(issecure_mask(SECURE_NO_SETUID_FIXUP))
#घोषणा SECBIT_NO_SETUID_FIXUP_LOCKED \
			(issecure_mask(SECURE_NO_SETUID_FIXUP_LOCKED))

/* When set, a process can retain its capabilities even after
   transitioning to a non-root user (the set-uid fixup suppressed by
   bit 2). Bit-4 is cleared when a process calls exec(); setting both
   bit 4 and 5 will create a barrier through exec that no exec()'d
   child can use this feature again. */
#घोषणा SECURE_KEEP_CAPS		4
#घोषणा SECURE_KEEP_CAPS_LOCKED		5  /* make bit-4 immutable */

#घोषणा SECBIT_KEEP_CAPS	(issecure_mask(SECURE_KEEP_CAPS))
#घोषणा SECBIT_KEEP_CAPS_LOCKED (issecure_mask(SECURE_KEEP_CAPS_LOCKED))

/* When set, a process cannot add new capabilities to its ambient set. */
#घोषणा SECURE_NO_CAP_AMBIENT_RAISE		6
#घोषणा SECURE_NO_CAP_AMBIENT_RAISE_LOCKED	7  /* make bit-6 immutable */

#घोषणा SECBIT_NO_CAP_AMBIENT_RAISE (issecure_mask(SECURE_NO_CAP_AMBIENT_RAISE))
#घोषणा SECBIT_NO_CAP_AMBIENT_RAISE_LOCKED \
			(issecure_mask(SECURE_NO_CAP_AMBIENT_RAISE_LOCKED))

#घोषणा SECURE_ALL_BITS		(issecure_mask(SECURE_NOROOT) | \
				 issecure_mask(SECURE_NO_SETUID_FIXUP) | \
				 issecure_mask(SECURE_KEEP_CAPS) | \
				 issecure_mask(SECURE_NO_CAP_AMBIENT_RAISE))
#घोषणा SECURE_ALL_LOCKS	(SECURE_ALL_BITS << 1)

#पूर्ण_अगर /* _UAPI_LINUX_SECUREBITS_H */
