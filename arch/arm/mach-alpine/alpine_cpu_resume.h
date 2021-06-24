<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Annapurna द_असल cpu-resume रेजिस्टर काष्ठाure.
 *
 * Copyright (C) 2015 Annapurna Lअसल Ltd.
 */

#अगर_अघोषित ALPINE_CPU_RESUME_H_
#घोषणा ALPINE_CPU_RESUME_H_

/* Per-cpu regs */
काष्ठा al_cpu_resume_regs_per_cpu अणु
	uपूर्णांक32_t	flags;
	uपूर्णांक32_t	resume_addr;
पूर्ण;

/* general regs */
काष्ठा al_cpu_resume_regs अणु
	/* Watermark क्रम validating the CPU resume काष्ठा */
	uपूर्णांक32_t watermark;
	uपूर्णांक32_t flags;
	काष्ठा al_cpu_resume_regs_per_cpu per_cpu[];
पूर्ण;

/* The expected magic number क्रम validating the resume addresses */
#घोषणा AL_CPU_RESUME_MAGIC_NUM		0xf0e1d200
#घोषणा AL_CPU_RESUME_MAGIC_NUM_MASK	0xffffff00

#पूर्ण_अगर /* ALPINE_CPU_RESUME_H_ */
