#include "include/buried.h"
#include "src/crypt/crypt.h"
#include "gtest/gtest.h"

TEST(BuriedBasicTest, Test1) { Buried_Create("D:/code/c++"); }

TEST(CryptTest, Test2) {
  std::string key = buried::AESCrypt::GetKey("salt", "password");
  EXPECT_TRUE(!key.empty());

  buried::Crypt *crypt = new buried::AESCrypt(key);
  std::string input = "Hello, world";
  std::string encrypt = crypt->Encrypt(input);
  EXPECT_TRUE(!encrypt.empty());
  std::string decrypt = crypt->Decrypt(encrypt);
  EXPECT_TRUE(!decrypt.empty());
  EXPECT_EQ(input, decrypt);
  delete crypt;
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}