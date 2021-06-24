<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ARM_COMPILER_H
#घोषणा __ASM_ARM_COMPILER_H

/*
 * This is used to ensure the compiler did actually allocate the रेजिस्टर we
 * asked it क्रम some अंतरभूत assembly sequences.  Apparently we can't trust
 * the compiler from one version to another so a bit of paranoia won't hurt.
 * This string is meant to be concatenated with the अंतरभूत यंत्र string and
 * will cause compilation to stop on mismatch.
 * (क्रम details, see gcc PR 15089)
 * For compatibility with clang, we have to specअगरically take the equivalence
 * of 'r11' <-> 'fp' and 'r12' <-> 'ip' पूर्णांकo account as well.
 */
#घोषणा __यंत्रeq(x, y)				\
	".ifnc " x "," y "; "			\
	  ".ifnc " x y ",fpr11; " 		\
	    ".ifnc " x y ",r11fp; "		\
	      ".ifnc " x y ",ipr12; " 		\
	        ".ifnc " x y ",r12ip; "		\
	          ".err; "			\
	        ".endif; "			\
	      ".endif; "			\
	    ".endif; "				\
	  ".endif; "				\
	".endif\n\t"


#पूर्ण_अगर /* __ASM_ARM_COMPILER_H */
