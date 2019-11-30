"""users table phone column

Revision ID: 2c39382cb489
Revises: 1b7bd43410a3
Create Date: 2019-04-21 14:59:16.466937

"""
from alembic import op
import sqlalchemy as sa


# revision identifiers, used by Alembic.
revision = '2c39382cb489'
down_revision = '1b7bd43410a3'
branch_labels = None
depends_on = None


def upgrade():
    # ### commands auto generated by Alembic - please adjust! ###
    op.add_column('user', sa.Column('phone', sa.String(length=15), nullable=True))
    op.create_index(op.f('ix_user_phone'), 'user', ['phone'], unique=False)
    # ### end Alembic commands ###


def downgrade():
    # ### commands auto generated by Alembic - please adjust! ###
    op.drop_index(op.f('ix_user_phone'), table_name='user')
    op.drop_column('user', 'phone')
    # ### end Alembic commands ###