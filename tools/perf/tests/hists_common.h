<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_TESTS__HISTS_COMMON_H__
#घोषणा __PERF_TESTS__HISTS_COMMON_H__

काष्ठा machine;
काष्ठा machines;

#घोषणा FAKE_PID_PERF1  100
#घोषणा FAKE_PID_PERF2  200
#घोषणा FAKE_PID_BASH   300

#घोषणा FAKE_MAP_PERF    0x400000
#घोषणा FAKE_MAP_BASH    0x400000
#घोषणा FAKE_MAP_LIBC    0x500000
#घोषणा FAKE_MAP_KERNEL  0xf00000
#घोषणा FAKE_MAP_LENGTH  0x100000

#घोषणा FAKE_SYM_OFFSET1  700
#घोषणा FAKE_SYM_OFFSET2  800
#घोषणा FAKE_SYM_OFFSET3  900
#घोषणा FAKE_SYM_LENGTH   100

#घोषणा FAKE_IP_PERF_MAIN  FAKE_MAP_PERF + FAKE_SYM_OFFSET1
#घोषणा FAKE_IP_PERF_RUN_COMMAND  FAKE_MAP_PERF + FAKE_SYM_OFFSET2
#घोषणा FAKE_IP_PERF_CMD_RECORD  FAKE_MAP_PERF + FAKE_SYM_OFFSET3
#घोषणा FAKE_IP_BASH_MAIN  FAKE_MAP_BASH + FAKE_SYM_OFFSET1
#घोषणा FAKE_IP_BASH_XMALLOC  FAKE_MAP_BASH + FAKE_SYM_OFFSET2
#घोषणा FAKE_IP_BASH_XFREE  FAKE_MAP_BASH + FAKE_SYM_OFFSET3
#घोषणा FAKE_IP_LIBC_MALLOC  FAKE_MAP_LIBC + FAKE_SYM_OFFSET1
#घोषणा FAKE_IP_LIBC_FREE  FAKE_MAP_LIBC + FAKE_SYM_OFFSET2
#घोषणा FAKE_IP_LIBC_REALLOC  FAKE_MAP_LIBC + FAKE_SYM_OFFSET3
#घोषणा FAKE_IP_KERNEL_SCHEDULE  FAKE_MAP_KERNEL + FAKE_SYM_OFFSET1
#घोषणा FAKE_IP_KERNEL_PAGE_FAULT  FAKE_MAP_KERNEL + FAKE_SYM_OFFSET2
#घोषणा FAKE_IP_KERNEL_SYS_PERF_EVENT_OPEN  FAKE_MAP_KERNEL + FAKE_SYM_OFFSET3

/*
 * The setup_fake_machine() provides a test environment which consists
 * of 3 processes that have 3 mappings and in turn, have 3 symbols
 * respectively.  See below table:
 *
 * Command:  Pid  Shared Object               Symbol
 * .............  .............  ...................
 *    perf:  100           perf  मुख्य
 *    perf:  100           perf  run_command
 *    perf:  100           perf  cmd_record
 *    perf:  100           libc  दो_स्मृति
 *    perf:  100           libc  मुक्त
 *    perf:  100           libc  पुनः_स्मृति
 *    perf:  100       [kernel]  schedule
 *    perf:  100       [kernel]  page_fault
 *    perf:  100       [kernel]  sys_perf_event_खोलो
 *    perf:  200           perf  मुख्य
 *    perf:  200           perf  run_command
 *    perf:  200           perf  cmd_record
 *    perf:  200           libc  दो_स्मृति
 *    perf:  200           libc  मुक्त
 *    perf:  200           libc  पुनः_स्मृति
 *    perf:  200       [kernel]  schedule
 *    perf:  200       [kernel]  page_fault
 *    perf:  200       [kernel]  sys_perf_event_खोलो
 *    bash:  300           bash  मुख्य
 *    bash:  300           bash  xदो_स्मृति
 *    bash:  300           bash  xमुक्त
 *    bash:  300           libc  दो_स्मृति
 *    bash:  300           libc  मुक्त
 *    bash:  300           libc  पुनः_स्मृति
 *    bash:  300       [kernel]  schedule
 *    bash:  300       [kernel]  page_fault
 *    bash:  300       [kernel]  sys_perf_event_खोलो
 */
काष्ठा machine *setup_fake_machine(काष्ठा machines *machines);

व्योम prपूर्णांक_hists_in(काष्ठा hists *hists);
व्योम prपूर्णांक_hists_out(काष्ठा hists *hists);

#पूर्ण_अगर /* __PERF_TESTS__HISTS_COMMON_H__ */
