<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1999, 2000, 2003 Ralf Baechle
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 */
#अगर_अघोषित _ASM_SIM_H
#घोषणा _ASM_SIM_H


#समावेश <यंत्र/यंत्र-offsets.h>

#घोषणा __str2(x) #x
#घोषणा __str(x) __str2(x)

#अगर_घोषित CONFIG_32BIT

#घोषणा save_अटल_function(symbol)					\
__यंत्र__(								\
	".text\n\t"							\
	".globl\t__" #symbol "\n\t"					\
	".align\t2\n\t"							\
	".type\t__" #symbol ", @function\n\t"				\
	".ent\t__" #symbol ", 0\n__"					\
	#symbol":\n\t"							\
	".frame\t$29, 0, $31\n\t"					\
	"sw\t$16,"__str(PT_R16)"($29)\t\t\t# save_static_function\n\t"	\
	"sw\t$17,"__str(PT_R17)"($29)\n\t"				\
	"sw\t$18,"__str(PT_R18)"($29)\n\t"				\
	"sw\t$19,"__str(PT_R19)"($29)\n\t"				\
	"sw\t$20,"__str(PT_R20)"($29)\n\t"				\
	"sw\t$21,"__str(PT_R21)"($29)\n\t"				\
	"sw\t$22,"__str(PT_R22)"($29)\n\t"				\
	"sw\t$23,"__str(PT_R23)"($29)\n\t"				\
	"sw\t$30,"__str(PT_R30)"($29)\n\t"				\
	"j\t" #symbol "\n\t"						\
	".end\t__" #symbol "\n\t"					\
	".size\t__" #symbol",. - __" #symbol)

#पूर्ण_अगर /* CONFIG_32BIT */

#अगर_घोषित CONFIG_64BIT

#घोषणा save_अटल_function(symbol)					\
__यंत्र__(								\
	".text\n\t"							\
	".globl\t__" #symbol "\n\t"					\
	".align\t2\n\t"							\
	".type\t__" #symbol ", @function\n\t"				\
	".ent\t__" #symbol ", 0\n__"					\
	#symbol":\n\t"							\
	".frame\t$29, 0, $31\n\t"					\
	"sd\t$16,"__str(PT_R16)"($29)\t\t\t# save_static_function\n\t"	\
	"sd\t$17,"__str(PT_R17)"($29)\n\t"				\
	"sd\t$18,"__str(PT_R18)"($29)\n\t"				\
	"sd\t$19,"__str(PT_R19)"($29)\n\t"				\
	"sd\t$20,"__str(PT_R20)"($29)\n\t"				\
	"sd\t$21,"__str(PT_R21)"($29)\n\t"				\
	"sd\t$22,"__str(PT_R22)"($29)\n\t"				\
	"sd\t$23,"__str(PT_R23)"($29)\n\t"				\
	"sd\t$30,"__str(PT_R30)"($29)\n\t"				\
	"j\t" #symbol "\n\t"						\
	".end\t__" #symbol "\n\t"					\
	".size\t__" #symbol",. - __" #symbol)

#पूर्ण_अगर /* CONFIG_64BIT */

#पूर्ण_अगर /* _ASM_SIM_H */
