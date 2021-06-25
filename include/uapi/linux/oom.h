<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI__INCLUDE_LINUX_OOM_H
#घोषणा _UAPI__INCLUDE_LINUX_OOM_H

/*
 * /proc/<pid>/oom_score_adj set to OOM_SCORE_ADJ_MIN disables oom समाप्तing क्रम
 * pid.
 */
#घोषणा OOM_SCORE_ADJ_MIN	(-1000)
#घोषणा OOM_SCORE_ADJ_MAX	1000

/*
 * /proc/<pid>/oom_adj set to -17 protects from the oom समाप्तer क्रम legacy
 * purposes.
 */
#घोषणा OOM_DISABLE (-17)
/* inclusive */
#घोषणा OOM_ADJUST_MIN (-16)
#घोषणा OOM_ADJUST_MAX 15

#पूर्ण_अगर /* _UAPI__INCLUDE_LINUX_OOM_H */
