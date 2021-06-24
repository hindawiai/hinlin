<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_KDEV_T_H
#घोषणा _LINUX_KDEV_T_H

#समावेश <uapi/linux/kdev_t.h>

#घोषणा MINORBITS	20
#घोषणा MINORMASK	((1U << MINORBITS) - 1)

#घोषणा MAJOR(dev)	((अचिन्हित पूर्णांक) ((dev) >> MINORBITS))
#घोषणा MINOR(dev)	((अचिन्हित पूर्णांक) ((dev) & MINORMASK))
#घोषणा MKDEV(ma,mi)	(((ma) << MINORBITS) | (mi))

#घोषणा prपूर्णांक_dev_t(buffer, dev)					\
	प्र_लिखो((buffer), "%u:%u\n", MAJOR(dev), MINOR(dev))

#घोषणा क्रमmat_dev_t(buffer, dev)					\
	(अणु								\
		प्र_लिखो(buffer, "%u:%u", MAJOR(dev), MINOR(dev));	\
		buffer;							\
	पूर्ण)

/* acceptable क्रम old fileप्रणालीs */
अटल __always_अंतरभूत bool old_valid_dev(dev_t dev)
अणु
	वापस MAJOR(dev) < 256 && MINOR(dev) < 256;
पूर्ण

अटल __always_अंतरभूत u16 old_encode_dev(dev_t dev)
अणु
	वापस (MAJOR(dev) << 8) | MINOR(dev);
पूर्ण

अटल __always_अंतरभूत dev_t old_decode_dev(u16 val)
अणु
	वापस MKDEV((val >> 8) & 255, val & 255);
पूर्ण

अटल __always_अंतरभूत u32 new_encode_dev(dev_t dev)
अणु
	अचिन्हित major = MAJOR(dev);
	अचिन्हित minor = MINOR(dev);
	वापस (minor & 0xff) | (major << 8) | ((minor & ~0xff) << 12);
पूर्ण

अटल __always_अंतरभूत dev_t new_decode_dev(u32 dev)
अणु
	अचिन्हित major = (dev & 0xfff00) >> 8;
	अचिन्हित minor = (dev & 0xff) | ((dev >> 12) & 0xfff00);
	वापस MKDEV(major, minor);
पूर्ण

अटल __always_अंतरभूत u64 huge_encode_dev(dev_t dev)
अणु
	वापस new_encode_dev(dev);
पूर्ण

अटल __always_अंतरभूत dev_t huge_decode_dev(u64 dev)
अणु
	वापस new_decode_dev(dev);
पूर्ण

अटल __always_अंतरभूत पूर्णांक sysv_valid_dev(dev_t dev)
अणु
	वापस MAJOR(dev) < (1<<14) && MINOR(dev) < (1<<18);
पूर्ण

अटल __always_अंतरभूत u32 sysv_encode_dev(dev_t dev)
अणु
	वापस MINOR(dev) | (MAJOR(dev) << 18);
पूर्ण

अटल __always_अंतरभूत अचिन्हित sysv_major(u32 dev)
अणु
	वापस (dev >> 18) & 0x3fff;
पूर्ण

अटल __always_अंतरभूत अचिन्हित sysv_minor(u32 dev)
अणु
	वापस dev & 0x3ffff;
पूर्ण

#पूर्ण_अगर
