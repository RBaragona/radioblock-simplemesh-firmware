/*
 * Copyright (c) 2011, SimpleMesh AUTHORS
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   1) Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *
 *   2) Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *
 *   3) Neither the name of the SimpleMesh AUTHORS nor the names of its contributors
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */
 
#include "sysQueue.h"

//#define QUEUE_DEBUG

#ifdef QUEUE_DEBUG
int SYS_QueueCount(SYS_Queue_t **queue);
void SYS_QueueValidate(SYS_Queue_t **queue);
#else
#define SYS_QueueCount(a) 0
#define SYS_QueueValidate(a)
#endif

/*****************************************************************************
*****************************************************************************/
void SYS_QueueAppend(SYS_Queue_t **queue, void *item)
{
  SYS_QueueValidate(queue);
  ((SYS_Queue_t *)item)->next = NULL;

  if (!*queue)
  {
    *queue = item;
  }
  else
  {
    SYS_Queue_t *last = *queue;
    while (last->next)
      last = last->next;
    last->next = item;
  }

  SYS_QueueValidate(queue);
}

/*****************************************************************************
*****************************************************************************/
void *SYS_QueueRemove(SYS_Queue_t **queue, void *item)
{
  SYS_QueueValidate(queue);

  if (*queue == item)
  {
    *queue = (*queue)->next;
  }
  else
  {
    SYS_Queue_t *prev = *queue;

    while (prev && prev->next != item)
      prev = prev->next;

    if (prev)
      prev->next = prev->next->next;
  }

  SYS_QueueValidate(queue);
  return item;
}
/*****************************************************************************
*****************************************************************************/
#ifdef QUEUE_DEBUG
int SYS_QueueCount(SYS_Queue_t **queue)
{
  SYS_QueueValidate(queue);

  int counter = 0;
  SYS_Queue_t * prev = *queue;

  while (prev) {
    prev = prev->next;
    counter++;
  }

  return counter;
}
/*****************************************************************************
*****************************************************************************/
void SYS_QueueValidate(SYS_Queue_t **queue)
{
  if ((*queue > 0) && (*queue < 0x1000)) {
    while(1);
  }
}
#endif
