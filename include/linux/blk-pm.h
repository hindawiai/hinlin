<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _BLK_PM_H_
#घोषणा _BLK_PM_H_

काष्ठा device;
काष्ठा request_queue;

/*
 * block layer runसमय pm functions
 */
#अगर_घोषित CONFIG_PM
बाह्य व्योम blk_pm_runसमय_init(काष्ठा request_queue *q, काष्ठा device *dev);
बाह्य पूर्णांक blk_pre_runसमय_suspend(काष्ठा request_queue *q);
बाह्य व्योम blk_post_runसमय_suspend(काष्ठा request_queue *q, पूर्णांक err);
बाह्य व्योम blk_pre_runसमय_resume(काष्ठा request_queue *q);
बाह्य व्योम blk_post_runसमय_resume(काष्ठा request_queue *q, पूर्णांक err);
बाह्य व्योम blk_set_runसमय_active(काष्ठा request_queue *q);
#अन्यथा
अटल अंतरभूत व्योम blk_pm_runसमय_init(काष्ठा request_queue *q,
				       काष्ठा device *dev) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _BLK_PM_H_ */
