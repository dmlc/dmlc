/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*!
 *  Copyright (c) 2015 by Contributors
 * \file recordio_split.h
 * \brief input split that splits recordio files
 * \author Tianqi Chen
 */
#ifndef DMLC_IO_RECORDIO_SPLIT_H_
#define DMLC_IO_RECORDIO_SPLIT_H_

#include <dmlc/io.h>
#include <dmlc/recordio.h>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include "./input_split_base.h"

namespace dmlc {
namespace io {
/*! \brief class that split the files by line */
class RecordIOSplitter : public InputSplitBase {
 public:
  RecordIOSplitter(FileSystem *fs,
                   const char *uri,
                   unsigned rank,
                   unsigned nsplit,
                   const bool recurse_directories) {
    this->Init(fs, uri, 4, recurse_directories);
    this->ResetPartition(rank, nsplit);
  }

  virtual bool ExtractNextRecord(Blob *out_rec, Chunk *chunk);

 protected:
  virtual size_t SeekRecordBegin(Stream *fi);
  virtual const char*
  FindLastRecordBegin(const char *begin, const char *end);
};
}  // namespace io
}  // namespace dmlc
#endif  // DMLC_IO_RECORDIO_SPLIT_H_
