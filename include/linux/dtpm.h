<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2020 Linaro Ltd
 *
 * Author: Daniel Lezcano <daniel.lezcano@linaro.org>
 */
#अगर_अघोषित ___DTPM_H__
#घोषणा ___DTPM_H__

#समावेश <linux/घातercap.h>

#घोषणा MAX_DTPM_DESCR 8
#घोषणा MAX_DTPM_CONSTRAINTS 1

काष्ठा dtpm अणु
	काष्ठा घातercap_zone zone;
	काष्ठा dtpm *parent;
	काष्ठा list_head sibling;
	काष्ठा list_head children;
	काष्ठा dtpm_ops *ops;
	अचिन्हित दीर्घ flags;
	u64 घातer_limit;
	u64 घातer_max;
	u64 घातer_min;
	पूर्णांक weight;
	व्योम *निजी;
पूर्ण;

काष्ठा dtpm_ops अणु
	u64 (*set_घातer_uw)(काष्ठा dtpm *, u64);
	u64 (*get_घातer_uw)(काष्ठा dtpm *);
	व्योम (*release)(काष्ठा dtpm *);
पूर्ण;

काष्ठा dtpm_descr;

प्रकार पूर्णांक (*dtpm_init_t)(काष्ठा dtpm_descr *);

काष्ठा dtpm_descr अणु
	काष्ठा dtpm *parent;
	स्थिर अक्षर *name;
	dtpm_init_t init;
पूर्ण;

/* Init section thermal table */
बाह्य काष्ठा dtpm_descr *__dtpm_table[];
बाह्य काष्ठा dtpm_descr *__dtpm_table_end[];

#घोषणा DTPM_TABLE_ENTRY(name)			\
	अटल typeof(name) *__dtpm_table_entry_##name	\
	__used __section("__dtpm_table") = &name

#घोषणा DTPM_DECLARE(name)	DTPM_TABLE_ENTRY(name)

#घोषणा क्रम_each_dtpm_table(__dtpm)	\
	क्रम (__dtpm = __dtpm_table;	\
	     __dtpm < __dtpm_table_end;	\
	     __dtpm++)

अटल अंतरभूत काष्ठा dtpm *to_dtpm(काष्ठा घातercap_zone *zone)
अणु
	वापस container_of(zone, काष्ठा dtpm, zone);
पूर्ण

पूर्णांक dtpm_update_घातer(काष्ठा dtpm *dtpm, u64 घातer_min, u64 घातer_max);

पूर्णांक dtpm_release_zone(काष्ठा घातercap_zone *pcz);

काष्ठा dtpm *dtpm_alloc(काष्ठा dtpm_ops *ops);

व्योम dtpm_unरेजिस्टर(काष्ठा dtpm *dtpm);

पूर्णांक dtpm_रेजिस्टर(स्थिर अक्षर *name, काष्ठा dtpm *dtpm, काष्ठा dtpm *parent);

पूर्णांक dtpm_रेजिस्टर_cpu(काष्ठा dtpm *parent);

#पूर्ण_अगर
