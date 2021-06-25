<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/* Copyright 2020 Qiang Yu <yuq825@gmail.com> */

#अगर_अघोषित __LIMA_DUMP_H__
#घोषणा __LIMA_DUMP_H__

#समावेश <linux/types.h>

/**
 * dump file क्रमmat क्रम all the inक्रमmation to start a lima task
 *
 * top level क्रमmat
 * | magic code "LIMA" | क्रमmat version | num tasks | data size |
 * | reserved | reserved | reserved | reserved |
 * | task 1 ID | task 1 size | num chunks | reserved | task 1 data |
 * | task 2 ID | task 2 size | num chunks | reserved | task 2 data |
 * ...
 *
 * task data क्रमmat
 * | chunk 1 ID | chunk 1 size | reserved | reserved | chunk 1 data |
 * | chunk 2 ID | chunk 2 size | reserved | reserved | chunk 2 data |
 * ...
 *
 */

#घोषणा LIMA_DUMP_MAJOR 1
#घोषणा LIMA_DUMP_MINOR 0

#घोषणा LIMA_DUMP_MAGIC 0x414d494c

काष्ठा lima_dump_head अणु
	__u32 magic;
	__u16 version_major;
	__u16 version_minor;
	__u32 num_tasks;
	__u32 size;
	__u32 reserved[4];
पूर्ण;

#घोषणा LIMA_DUMP_TASK_GP   0
#घोषणा LIMA_DUMP_TASK_PP   1
#घोषणा LIMA_DUMP_TASK_NUM  2

काष्ठा lima_dump_task अणु
	__u32 id;
	__u32 size;
	__u32 num_chunks;
	__u32 reserved;
पूर्ण;

#घोषणा LIMA_DUMP_CHUNK_FRAME         0
#घोषणा LIMA_DUMP_CHUNK_BUFFER        1
#घोषणा LIMA_DUMP_CHUNK_PROCESS_NAME  2
#घोषणा LIMA_DUMP_CHUNK_PROCESS_ID    3
#घोषणा LIMA_DUMP_CHUNK_NUM           4

काष्ठा lima_dump_chunk अणु
	__u32 id;
	__u32 size;
	__u32 reserved[2];
पूर्ण;

काष्ठा lima_dump_chunk_buffer अणु
	__u32 id;
	__u32 size;
	__u32 va;
	__u32 reserved;
पूर्ण;

काष्ठा lima_dump_chunk_pid अणु
	__u32 id;
	__u32 size;
	__u32 pid;
	__u32 reserved;
पूर्ण;

#पूर्ण_अगर
