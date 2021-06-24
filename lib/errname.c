<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/build_bug.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/errname.h>
#समावेश <linux/kernel.h>
#समावेश <linux/गणित.स>

/*
 * Ensure these tables करो not accidentally become gigantic अगर some
 * huge त्रुटि_सं makes it in. On most architectures, the first table will
 * only have about 140 entries, but mips and parisc have more sparsely
 * allocated त्रुटि_संs (with EHWPOISON = 257 on parisc, and EDQUOT = 1133
 * on mips), so this wastes a bit of space on those - though we
 * special हाल the EDQUOT हाल.
 */
#घोषणा E(err) [err + BUILD_BUG_ON_ZERO(err <= 0 || err > 300)] = "-" #err
अटल स्थिर अक्षर *names_0[] = अणु
	E(E2BIG),
	E(EACCES),
	E(EADDRINUSE),
	E(EADDRNOTAVAIL),
	E(EADV),
	E(EAFNOSUPPORT),
	E(EALREADY),
	E(EBADE),
	E(EBADF),
	E(EBADFD),
	E(EBADMSG),
	E(EBADR),
	E(EBADRQC),
	E(EBADSLT),
	E(EBFONT),
	E(EBUSY),
#अगर_घोषित ECANCELLED
	E(ECANCELLED),
#पूर्ण_अगर
	E(ECHILD),
	E(ECHRNG),
	E(ECOMM),
	E(ECONNABORTED),
	E(ECONNRESET),
	E(EDEADLOCK),
	E(EDESTADDRREQ),
	E(गलत_तर्क),
	E(EDOTDOT),
#अगर_अघोषित CONFIG_MIPS
	E(EDQUOT),
#पूर्ण_अगर
	E(EEXIST),
	E(EFAULT),
	E(EFBIG),
	E(EHOSTDOWN),
	E(EHOSTUNREACH),
	E(EHWPOISON),
	E(EIDRM),
	E(EILSEQ),
#अगर_घोषित EINIT
	E(EINIT),
#पूर्ण_अगर
	E(EINPROGRESS),
	E(EINTR),
	E(EINVAL),
	E(EIO),
	E(EISCONN),
	E(EISसूची),
	E(EISNAM),
	E(EKEYEXPIRED),
	E(EKEYREJECTED),
	E(EKEYREVOKED),
	E(EL2HLT),
	E(EL2NSYNC),
	E(EL3HLT),
	E(EL3RST),
	E(ELIBACC),
	E(ELIBBAD),
	E(ELIBEXEC),
	E(ELIBMAX),
	E(ELIBSCN),
	E(ELNRNG),
	E(ELOOP),
	E(EMEDIUMTYPE),
	E(EMखाता),
	E(EMLINK),
	E(EMSGSIZE),
	E(EMULTIHOP),
	E(ENAMETOOLONG),
	E(ENAVAIL),
	E(ENETDOWN),
	E(ENETRESET),
	E(ENETUNREACH),
	E(ENखाता),
	E(ENOANO),
	E(ENOBUFS),
	E(ENOCSI),
	E(ENODATA),
	E(ENODEV),
	E(ENOENT),
	E(ENOEXEC),
	E(ENOKEY),
	E(ENOLCK),
	E(ENOLINK),
	E(ENOMEDIUM),
	E(ENOMEM),
	E(ENOMSG),
	E(ENONET),
	E(ENOPKG),
	E(ENOPROTOOPT),
	E(ENOSPC),
	E(ENOSR),
	E(ENOSTR),
#अगर_घोषित ENOSYM
	E(ENOSYM),
#पूर्ण_अगर
	E(ENOSYS),
	E(ENOTBLK),
	E(ENOTCONN),
	E(ENOTसूची),
	E(ENOTEMPTY),
	E(ENOTNAM),
	E(ENOTRECOVERABLE),
	E(ENOTSOCK),
	E(ENOTTY),
	E(ENOTUNIQ),
	E(ENXIO),
	E(EOPNOTSUPP),
	E(EOVERFLOW),
	E(EOWNERDEAD),
	E(EPERM),
	E(EPFNOSUPPORT),
	E(EPIPE),
#अगर_घोषित EPROCLIM
	E(EPROCLIM),
#पूर्ण_अगर
	E(EPROTO),
	E(EPROTONOSUPPORT),
	E(EPROTOTYPE),
	E(दुस्फल),
	E(EREMCHG),
#अगर_घोषित EREMDEV
	E(EREMDEV),
#पूर्ण_अगर
	E(EREMOTE),
	E(EREMOTEIO),
#अगर_घोषित EREMOTERELEASE
	E(EREMOTERELEASE),
#पूर्ण_अगर
	E(ERESTART),
	E(ERFKILL),
	E(EROFS),
#अगर_घोषित ERREMOTE
	E(ERREMOTE),
#पूर्ण_अगर
	E(ESHUTDOWN),
	E(ESOCKTNOSUPPORT),
	E(ESPIPE),
	E(ESRCH),
	E(ESRMNT),
	E(ESTALE),
	E(ESTRPIPE),
	E(ETIME),
	E(ETIMEDOUT),
	E(ETOOMANYREFS),
	E(ETXTBSY),
	E(EUCLEAN),
	E(EUNATCH),
	E(EUSERS),
	E(EXDEV),
	E(EXFULL),

	E(ECANCELED), /* ECANCELLED */
	E(EAGAIN), /* EWOULDBLOCK */
	E(ECONNREFUSED), /* EREFUSED */
	E(EDEADLK), /* EDEADLOCK */
पूर्ण;
#अघोषित E

#घोषणा E(err) [err - 512 + BUILD_BUG_ON_ZERO(err < 512 || err > 550)] = "-" #err
अटल स्थिर अक्षर *names_512[] = अणु
	E(ERESTARTSYS),
	E(ERESTARTNOINTR),
	E(ERESTARTNOHAND),
	E(ENOIOCTLCMD),
	E(ERESTART_RESTARTBLOCK),
	E(EPROBE_DEFER),
	E(EOPENSTALE),
	E(ENOPARAM),

	E(EBADHANDLE),
	E(ENOTSYNC),
	E(EBADCOOKIE),
	E(ENOTSUPP),
	E(ETOOSMALL),
	E(ESERVERFAULT),
	E(EBADTYPE),
	E(EJUKEBOX),
	E(EIOCBQUEUED),
	E(ERECALLCONFLICT),
पूर्ण;
#अघोषित E

अटल स्थिर अक्षर *__errname(अचिन्हित err)
अणु
	अगर (err < ARRAY_SIZE(names_0))
		वापस names_0[err];
	अगर (err >= 512 && err - 512 < ARRAY_SIZE(names_512))
		वापस names_512[err - 512];
	/* But why? */
	अगर (IS_ENABLED(CONFIG_MIPS) && err == EDQUOT) /* 1133 */
		वापस "-EDQUOT";
	वापस शून्य;
पूर्ण

/*
 * errname(EIO) -> "EIO"
 * errname(-EIO) -> "-EIO"
 */
स्थिर अक्षर *errname(पूर्णांक err)
अणु
	स्थिर अक्षर *name = __errname(असल(err));
	अगर (!name)
		वापस शून्य;

	वापस err > 0 ? name + 1 : name;
पूर्ण
