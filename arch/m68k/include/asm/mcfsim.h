<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/****************************************************************************/

/*
 *	mcfsim.h -- ColdFire System Integration Module support.
 *
 *	(C) Copyright 1999-2003, Greg Ungerer (gerg@snapgear.com)
 * 	(C) Copyright 2000, Lineo Inc. (www.lineo.com)
 */

/****************************************************************************/
#अगर_अघोषित	mcfsim_h
#घोषणा	mcfsim_h
/****************************************************************************/

/*
 * Include the appropriate ColdFire CPU specअगरic System Integration Module
 * (SIM) definitions.
 */
#अगर defined(CONFIG_M5206) || defined(CONFIG_M5206e)
#समावेश <यंत्र/m5206sim.h>
#समावेश <यंत्र/mcfपूर्णांकc.h>
#या_अगर defined(CONFIG_M520x)
#समावेश <यंत्र/m520xsim.h>
#या_अगर defined(CONFIG_M523x)
#समावेश <यंत्र/m523xsim.h>
#समावेश <यंत्र/mcfपूर्णांकc.h>
#या_अगर defined(CONFIG_M5249) || defined(CONFIG_M525x)
#समावेश <यंत्र/m525xsim.h>
#समावेश <यंत्र/mcfपूर्णांकc.h>
#या_अगर defined(CONFIG_M527x)
#समावेश <यंत्र/m527xsim.h>
#या_अगर defined(CONFIG_M5272)
#समावेश <यंत्र/m5272sim.h>
#या_अगर defined(CONFIG_M528x)
#समावेश <यंत्र/m528xsim.h>
#या_अगर defined(CONFIG_M5307)
#समावेश <यंत्र/m5307sim.h>
#समावेश <यंत्र/mcfपूर्णांकc.h>
#या_अगर defined(CONFIG_M53xx)
#समावेश <यंत्र/m53xxsim.h>
#या_अगर defined(CONFIG_M5407)
#समावेश <यंत्र/m5407sim.h>
#समावेश <यंत्र/mcfपूर्णांकc.h>
#या_अगर defined(CONFIG_M54xx)
#समावेश <यंत्र/m54xxsim.h>
#या_अगर defined(CONFIG_M5441x)
#समावेश <यंत्र/m5441xsim.h>
#पूर्ण_अगर

/****************************************************************************/
#पूर्ण_अगर	/* mcfsim_h */
