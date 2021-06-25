<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_HIGHUID_H
#घोषणा _LINUX_HIGHUID_H

#समावेश <linux/types.h>

/*
 * general notes:
 *
 * CONFIG_UID16 is defined अगर the given architecture needs to
 * support backwards compatibility क्रम old प्रणाली calls.
 *
 * kernel code should use uid_t and gid_t at all बार when dealing with
 * kernel-निजी data.
 *
 * old_uid_t and old_gid_t should only be dअगरferent अगर CONFIG_UID16 is
 * defined, अन्यथा the platक्रमm should provide dummy प्रकारs क्रम them
 * such that they are equivalent to __kernel_अणुu,gपूर्णid_t.
 *
 * uid16_t and gid16_t are used on all architectures. (when dealing
 * with काष्ठाures hard coded to 16 bits, such as in fileप्रणालीs)
 */


/*
 * This is the "overflow" UID and GID. They are used to signअगरy uid/gid
 * overflow to old programs when they request uid/gid inक्रमmation but are
 * using the old 16 bit पूर्णांकerfaces.
 * When you run a libc5 program, it will think that all highuid files or
 * processes are owned by this uid/gid.
 * The idea is that it's better to करो so than possibly वापस 0 in lieu of
 * 65536, etc.
 */

बाह्य पूर्णांक overflowuid;
बाह्य पूर्णांक overflowgid;

बाह्य व्योम __bad_uid(व्योम);
बाह्य व्योम __bad_gid(व्योम);

#घोषणा DEFAULT_OVERFLOWUID	65534
#घोषणा DEFAULT_OVERFLOWGID	65534

#अगर_घोषित CONFIG_UID16

/* prevent uid mod 65536 effect by वापसing a शेष value क्रम high UIDs */
#घोषणा high2lowuid(uid) ((uid) & ~0xFFFF ? (old_uid_t)overflowuid : (old_uid_t)(uid))
#घोषणा high2lowgid(gid) ((gid) & ~0xFFFF ? (old_gid_t)overflowgid : (old_gid_t)(gid))
/*
 * -1 is dअगरferent in 16 bits than it is in 32 bits
 * these macros are used by chown(), setreuid(), ...,
 */
#घोषणा low2highuid(uid) ((uid) == (old_uid_t)-1 ? (uid_t)-1 : (uid_t)(uid))
#घोषणा low2highgid(gid) ((gid) == (old_gid_t)-1 ? (gid_t)-1 : (gid_t)(gid))

#घोषणा __convert_uid(size, uid) \
	(size >= माप(uid) ? (uid) : high2lowuid(uid))
#घोषणा __convert_gid(size, gid) \
	(size >= माप(gid) ? (gid) : high2lowgid(gid))
	

#अन्यथा

#घोषणा __convert_uid(size, uid) (uid)
#घोषणा __convert_gid(size, gid) (gid)

#पूर्ण_अगर /* !CONFIG_UID16 */

/* uid/gid input should be always 32bit uid_t */
#घोषणा SET_UID(var, uid) करो अणु (var) = __convert_uid(माप(var), (uid)); पूर्ण जबतक (0)
#घोषणा SET_GID(var, gid) करो अणु (var) = __convert_gid(माप(var), (gid)); पूर्ण जबतक (0)

/*
 * Everything below this line is needed on all architectures, to deal with
 * fileप्रणालीs that only store 16 bits of the UID/GID, etc.
 */

/*
 * This is the UID and GID that will get written to disk अगर a fileप्रणाली
 * only supports 16-bit UIDs and the kernel has a high UID/GID to ग_लिखो
 */
बाह्य पूर्णांक fs_overflowuid;
बाह्य पूर्णांक fs_overflowgid;

#घोषणा DEFAULT_FS_OVERFLOWUID	65534
#घोषणा DEFAULT_FS_OVERFLOWGID	65534

/*
 * Since these macros are used in architectures that only need limited
 * 16-bit UID back compatibility, we won't use old_uid_t and old_gid_t
 */
#घोषणा fs_high2lowuid(uid) ((uid) & ~0xFFFF ? (uid16_t)fs_overflowuid : (uid16_t)(uid))
#घोषणा fs_high2lowgid(gid) ((gid) & ~0xFFFF ? (gid16_t)fs_overflowgid : (gid16_t)(gid))

#घोषणा low_16_bits(x)	((x) & 0xFFFF)
#घोषणा high_16_bits(x)	(((x) & 0xFFFF0000) >> 16)

#पूर्ण_अगर /* _LINUX_HIGHUID_H */
